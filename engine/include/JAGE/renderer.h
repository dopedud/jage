#pragma once

#include "JAGE/core.h"
#include "JAGE/math.h"
#include "JAGE/assets.h"

namespace JAGE
{
    // forward declare Renderer class to be used by the Resource classes
    class JAGE_API Renderer;

    // forward declare DebugRenderer class to be used by the Window class
    class JAGE_API DebugRenderer;

    /**
     * @namespace Resource
     * 
     * @brief The `Resource` namespace that contains representations of different GPU resources.
     * 
     * "Resource" in the context of game engines can refer to a wide variety of meaning, including memory resources and
     * persistent resources (files that live on the hard disk). However in JAGE specifically, "Resource" means GPU
     * resource, which are data that is uploaded from CPU to GPU, and stay in GPU memory. It could also represent
     * graphics resources that are not directly associated with memory on the GPU, such as materials.
     */
    namespace Resource
    {
        using ID = u64;

        template<typename T>
        class Handle
        {
        public:
            Handle() = default;
            Handle(ID id, T* resource);

            ID id() const;
            T* resource() const;
            bool is_valid() const;
        private:
            ID m_id {};
            T* m_resource {};
        };

        /**
         * @class Resource::Base
         * 
         * @brief The `Resource::Base` class that acts as a base class for all the different types of GPU resources to
         * derive from.
         * 
         */
        class JAGE_API Base
        {
        public:
            static LogicalPath dir_path();

            Base(Data::URI uri);
            virtual ~Base() = default;

            Data::URI uri() const;
            bool is_valid() const;
        protected:
            Data::URI m_uri;
            bool m_valid;
        };

        class JAGE_API Shader : public Base
        {
        public:
            enum class DataType : u8
            {
                None = 0,
                Float, Float2, Float3, Float4,
                Int, Int2, Int3, Int4,
                Mat3, Mat4,
                Bool
            };

            static LogicalPath dir_path();

            static unsigned datatype_size(DataType datatype);

            Shader(Data::URI uri);

            virtual void bind()     const = 0;
            virtual void unbind()   const = 0;

            virtual void set_uniform_bool       (std::string_view name, bool value)                 = 0;
            virtual void set_uniform_uint       (std::string_view name, unsigned value)             = 0;
            virtual void set_uniform_int        (std::string_view name, int value)                  = 0;
            virtual void set_uniform_float      (std::string_view name, float value)                = 0;
            virtual void set_uniform_float2     (std::string_view name, const glm::vec2& value)     = 0;
            virtual void set_uniform_float3     (std::string_view name, const glm::vec3& value)     = 0;
            virtual void set_uniform_float4     (std::string_view name, const glm::vec4& value)     = 0;
            virtual void set_uniform_mat4       (std::string_view name, const glm::mat4& value)     = 0;

        private:
            static std::unique_ptr<Shader> Create
            (
                Data::URI uri,
                std::string_view vs_str,
                std::string_view fs_str,
                std::string_view gs_str = ""sv
            );

            friend class JAGE::Renderer;
        };

        class JAGE_API Texture : public Base
        {
        public:
            static LogicalPath dir_path();

            Texture(Data::URI uri);

            virtual void bind(unsigned texture_unit)    const = 0;
            virtual void unbind()                       const = 0;
        private:
            static std::unique_ptr<Texture> Create(Data::URI uri, const Data::Image* imagedata);

            friend class JAGE::Renderer;
        };

        class JAGE_API Material : public Base
        {
        public:
            enum class FaceCullingMode : u8 { NONE = 0, BACK, FRONT };

            static LogicalPath dir_path();

            Material
            (
                Data::URI uri, 
                const Data::Material* materialdata,
                Handle<Shader> shader,
                Handle<Texture> albedo_texture
            );

            const Data::Material* materialdata() const;

            Handle<Shader> shader() const;

            Handle<Texture> albedo_texture() const;

            FaceCullingMode face_culling_mode() const;
            void set_face_culling_mode(FaceCullingMode mode);
        private:
            static std::unique_ptr<Material> Create
            (
                Data::URI uri,
                const Data::Material* materialdata,
                Handle<Shader> shader,
                Handle<Texture> albedo_texture
            );

            const Data::Material* m_materialdata;
            Handle<Shader> m_shader;
            Handle<Texture> m_albedo_texture;
            FaceCullingMode m_face_culling_mode;

            friend class JAGE::Renderer;
        };

        class JAGE_API Mesh : public Base
        {
        public:
            static LogicalPath dir_path();

            Mesh(Data::URI uri, const Data::Mesh* meshdata);

            virtual void render(Handle<Material> material) = 0;
        protected:
            const Data::Mesh* m_meshdata;
        private:
            static std::unique_ptr<Mesh> Create(Data::URI uri, const Data::Mesh* meshdata);

            friend class JAGE::Renderer;
        };
    }

    // forward declare Window class to be used by Layer class
    class JAGE_API Window;

    class JAGE_API Layer
    {
    public:
        Layer(Window* window, std::string_view name = "Unnamed Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;

        virtual void OnUpdate() = 0;

        virtual void OnEvent(const Event& e) = 0;

        std::string_view name() const { return m_name; }
    protected:
        Window* m_window;
        const std::string m_name;
    };

    using EventCallbackFn = std::function<void(const Event&)>;

    class JAGE_API Window
    {
    public:
        /**
         * @struct Window::Properties
         * @brief The `Window::Properties` structure that holds data for properties of a window.
         * 
         * The data was defined as a seperate structure to allow callbacks from the window manager.
         */
        struct JAGE_API Properties
        {
            std::string title { "JAGE Engine" };
            unsigned width { 1280 }, height { 720 };
            bool vsync { false };

            Properties
            (
                std::string_view title = "JAGE Engine",
                unsigned width = 1280,
                unsigned height = 720,
                bool vsync = false
            );
        };

        static std::unique_ptr<Window> Create(const Properties& properties = Properties{});
        Window(const Properties& properties);
        virtual ~Window() = default;

        unsigned width() const;
        unsigned height() const;

        float aspect_ratio() const;

        bool vsync() const;
        virtual void set_vsync(bool enabled) = 0;

        Renderer* renderer() const;
        DebugRenderer* debug_renderer() const;

        void set_eventcallback(const EventCallbackFn& callback);

        virtual void OnUpdate() = 0;

        /**
         * @fn handle
         * @brief A function to expose backend implementation of a window.
         * 
         * @note This should be used only if you know what you're doing.
         */
        virtual void* handle() = 0;

        void OnEvent(const Event& e);

        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> overlay);
        // void PopLayer(std::unique_ptr<Layer> layer);
        // void PopOverlay(std::unique_ptr<Layer> overlay);
    protected:
        /**
         * @struct Window::Data
         * @brief The `Window::Data` structure that holds additional data of a window, particularly event callbacks.
         * 
         * This is the data that's being passed in a callback of an event for a window manager to call when a window
         * event occurs.
         */
        struct Data
        {
            Properties properties;
            EventCallbackFn callback;
            EventCallbackFn OnEvent;
        };

        Data data;

        std::vector<std::unique_ptr<Layer>> layers;
        int layer_insert_index;

        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<DebugRenderer> m_debug_renderer;
    };

    class JAGE_API Renderer
    {
    public:
        static std::unique_ptr<Renderer> Create(Window* window);
        Renderer(Window* window);
        virtual ~Renderer() = default;

        void set_vp(const glm::mat4& view, const glm::mat4& projection);

        const glm::mat4& view() const;
        const glm::mat4& projection() const;

        Resource::Handle<Resource::Shader> CreateShader
        (
            Asset::Handle<Asset::Text> vs_asset,
            Asset::Handle<Asset::Text> fs_asset,
            Asset::Handle<Asset::Text> gs_asset = Asset::Handle<Asset::Text>{}
        );

        Resource::Handle<Resource::Texture> CreateTexture(Asset::Handle<Asset::Image> image_asset);

        Resource::Handle<Resource::Material> CreateMaterial
        (
            Asset::Handle<Asset::Model> model_asset,
            Resource::Handle<Resource::Shader> shader,
            unsigned mat_index
        );

        Resource::Handle<Resource::Mesh> CreateMesh(Asset::Handle<Asset::Model> model_asset, unsigned mesh_index);

        Resource::Handle<Resource::Texture> ErrorTexture();
    protected:
        Window* m_window;

        glm::mat4 m_view, m_projection;

        Resource::Handle<Resource::Texture> CreateTexture(const Data::Image* imagedata);

        std::unordered_map<Resource::ID, std::unique_ptr<Resource::Shader>>     shader_resources;
        std::unordered_map<Resource::ID, std::unique_ptr<Resource::Texture>>    texture_resources;
        std::unordered_map<Resource::ID, std::unique_ptr<Resource::Material>>   material_resources;
        std::unordered_map<Resource::ID, std::unique_ptr<Resource::Mesh>>       mesh_resources;
    };

    class JAGE_API DebugRenderer
    {
    public:
        static std::unique_ptr<DebugRenderer> Create(Window* window);
        DebugRenderer(Window* window);
        virtual ~DebugRenderer() = default;

        /**
         * @fn RenderGridLines
         * @brief Render grid lines in the game world.
         * 
         * Ideally, `slices` should take even values to get half slices correctly. Odd values will be truncated to the
         * lowest and nearest even value.
         * 
         * @param slices  Number of slices. Note that the slices start from the center of the grid (meaning that if you
         * set this value to, for example, 5 slices, you'll get 10 slices total).
         * @param spacing Spacing between slices. 
         */
        virtual void RenderGridLines(unsigned slices = 5, float spacing = 25.0f) = 0;

        virtual void RenderBaseAxes(float size = 0.1f) = 0;

        void set_vp(glm::mat4 view, glm::mat4 projection);
    protected:
        Window* m_window;

        glm::mat4 m_view, m_projection;
    };

    struct JAGE_API BufferElement
    {
        Resource::Shader::DataType shader_datatype;
        std::string name;
        unsigned size;
        unsigned offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(Resource::Shader::DataType shader_datatype, std::string_view name, bool normalized = false);

        unsigned component_count() const;
    };

    class JAGE_API BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        const std::vector<BufferElement>& elements() const;
        unsigned stride() const;
    private:
        std::vector<BufferElement> m_elements {};
        unsigned m_stride;
    };
}

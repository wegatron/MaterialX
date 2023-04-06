#pragma once

#include <string>

namespace x_engine
{
    namespace samples {
        class Window
        {
        public:
            struct Extent
            {
                uint32_t width;
                uint32_t height;
            };

            enum class Mode
            {
                Headless,
                Fullscreen,
                FullscreenBorderless,
                FullscreenStretch,
                Default
            };
           
            struct Properties
            {
                std::string title     = "";
                bool        resizable = true;
                Extent      extent    = {1280, 720};                
            };

            /**
             * @brief Constructs a Window
             * @param properties The preferred configuration of the window
             */
            Window(const Properties &properties) : properties_(properties) {}

            virtual ~Window() = default;

            /**
             * @brief Checks if the window should be closed
             */
            virtual bool should_close() = 0;

            /**
             * @brief Handles the processing of all underlying window events
             */
            virtual void process_events() = 0;

            /**
             * @brief Requests to close the window
             */
            virtual void close() = 0;

            /**
             * @return The dot-per-inch scale factor
             */
            virtual float get_dpi_factor() const = 0;

            /**
             * @return The scale factor for systems with heterogeneous window and pixel coordinates
             */
	    virtual float get_content_scale_factor() const = 0;

	    virtual void * get_handle() = 0;

            /**
             * @brief Attempt to resize the window - not guaranteed to change
             * 
             * @param extent The preferred window extent
             * @return Extent The new window extent
             */
            Extent resize(const Extent &extent)
	        {
	            if(properties_.resizable)
		            properties_.extent=extent;
                return properties_.extent;
            }

            const Extent &get_extent() const {
    	      return properties_.extent;
	        }            

        protected:
            Properties properties_;
        };
    }
}

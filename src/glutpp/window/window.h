#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <glutpp/config.h>
#include <glutpp/renderable.h>
#include <glutpp/window/desc.h>
#include <glutpp/texture.h>
#include <glutpp/camera.h>
#include <glutpp/light/light.h>
#include <glutpp/master.h>
#include <glutpp/glsl/program.h>
#include <glutpp/glsl/shader.h>
#include <glutpp/gui/layout.h>

#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <gal/sig/signal.h>
#include <gal/flag.h>

void	checkerror(char const *);

namespace glutpp {
	namespace window {
		class window: public std::enable_shared_from_this<window>, public gal::flag<unsigned int> {
			protected:
				
			public:
				struct flag {
					enum e {
						SHOULD_RELEASE = 1 << 0,
					};
				};


				window(glutpp::window::desc_s desc);
				~window();
				unsigned int f();
				void	f(unsigned int flag);
				void	init();
				void	render(double time);
				void	step(double time);

				void	resize();
				void	set_layout(glutpp::gui::layout_s layout);
				void	i(int ni);
				void	set_scene(glutpp::scene::scene_s scene);

				void	callback_window_pos_fun(GLFWwindow*,int,int);
				void	callback_window_size_fun(GLFWwindow*,int,int);
				void	callback_window_close_fun(GLFWwindow*);
				void	callback_window_refresh_fun(GLFWwindow*);
				void	callback_mouse_button_fun(GLFWwindow*,int,int,int);
				void	callback_key_fun(GLFWwindow*,int,int,int,int);
			public:
				// input signals
				struct
				{
					gal::sig::signal<int,int,int,int>	key_fun_;
					gal::sig::signal<int,int,int>		mouse_button_fun_;
				} sig_;


				/*				char const *			title_;
								int				w_;
								int				h_;
								int				x_;
								int				y_;
				 */
				glutpp::renderable_s		renderable_;


				int			i_;
				glutpp::window::raw	raw_;

				GLFWwindow*		window_;
				
				//int			windowID;

			public:

		};
	}
}


#endif









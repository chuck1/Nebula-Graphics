#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

#include <boost/weak_ptr.hpp>

#include <Nebula/config.hpp>
#include <Nebula/Types.hpp>
#include <Nebula/Graphics/Camera/View/Base.hpp>
#include <Nebula/Graphics/texture.hpp>
#include <Nebula/Graphics/Light/desc.hpp>
#include <Nebula/Graphics/Light/raw.hpp>

//#include <math/color.hpp>

namespace Neb {
	namespace Light {
		class light { //: public gal::flag {
			public:
				
				light(Neb::Shape::shape_w);

				void				i(int const &);
				int const &			i() const;

				void				init(Neb::Light::desc_w);

				virtual void			release();
				virtual void			cleanup();
				void				step(double) {}
				void				load(int, physx::PxMat44);

				void				load_shadow();
				void				draw();
				void				dim();
				void				RenderShadowPost();
				void				RenderLightPOV();


				void				notify_foundation_change_pose();
				physx::PxMat44			get_pose();
				physx::PxVec4			get_pos();
			private:
				//gal::flag::flag_type const &		f() const;
				//void					f(gal::flag::flag_type const &);
			public:

				int				i_;
				Raw				raw_;

				texture				texture_shadow_map_;

				//Neb::scene::scene_w		scene_;
				boost::weak_ptr<Neb::Shape::shape>			shape_;

		};
	}
}

#endif
#ifndef __GLUTPP_SHAPE_H__
#define __GLUTPP_SHAPE_H__

#include <map>

#include <boost/weak_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>

/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <gru/config.hpp>
#include <gru/shape/raw.hpp>
#include <gru/shape/parent.hpp>
#include <gru/master.hpp>
#include <gru/Graphics/glsl/program.hpp>
#include <gru/Graphics/light/light.hpp>
#include <gru/Graphics/material.hpp>
#include <gru/Graphics/mesh.hpp>

namespace glutpp {
	namespace shape {
		class buffer {
			public:
				GLuint		vbo_;
				GLuint		indices_;

				struct
				{
					std::shared_ptr<glutpp::texture>	image_;
				} texture_;
		};


		class shape:
			virtual public glutpp::shape::parent,
			public gal::flag<unsigned int>
		{
			public:
				typedef std::shared_ptr<glutpp::shape::buffer>		buffer_t;
				typedef std::map<glutpp::window::window*,buffer_t>	map_t;



				shape(boost::shared_ptr<glutpp::shape::parent> parent);
				~shape();
				
				physx::PxMat44					getPose();
				physx::PxMat44					getPoseGlobal();
				boost::shared_ptr<glutpp::shape::parent>	getParent();


				void			init(boost::shared_ptr<glutpp::shape::desc> desc);

				virtual void		createMesh() = 0;
				
				void			release();
				void			cleanup();
				void			step(double time);
				void			notify_foundation_change_pose();
				
				/** @name Rendering @{ */
				void			load_lights(int& i, physx::PxMat44 space);

				void			draw(glutpp::window::window_s, physx::PxMat44 space);
	
				void			model_load(physx::PxMat44 space);
				void			init_buffer(glutpp::window::window_s, std::shared_ptr<glutpp::glsl::program> p);

				virtual void		draw_elements(glutpp::window::window_s, physx::PxMat44 space);
				/** @} */
				/** @name Index
				 * @{
				 */
				void		i(int ni);
				int		i();
				/** @} */
				/** @name Flag
				 * @{
				 */
				unsigned int	f();
				void		f(unsigned int flag);
				/** @} */
			public:
				// draw data

				/** @brief ID */
				int					i_;
				/** @brief Raw data. */
				glutpp::shape::Raw			raw_;
				
				Neb::Map<glutpp::light::light>		lights_;
				Neb::Map<glutpp::shape::shape>		shapes_;

				glutpp::material::material		material_front_;
				mesh					mesh_;

				map_t					context_;

				glutpp::program_name::e			program_;

				boost::weak_ptr<glutpp::shape::parent>		parent_;
		};
		namespace Box {
			class Box: public glutpp::shape::shape {
				virtual void		createMesh();
			};
		}
		namespace Sphere {
			class Sphere: public glutpp::shape::shape {
				virtual void		createMesh();
			};
		}
		namespace Empty {
			class Empty: public glutpp::shape::shape {
				virtual void		createMesh();

				virtual void		draw_elements(glutpp::window::window_s, physx::PxMat44 space) {}
			};
		}
	}
}

#endif




#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <memory>
#include <string>

#include <GLFW/glfw3.h>

//#include <PxPhysicsAPI.h>
#include <Nebula/Util/typedef.hpp>

//#include <math/mat44.hpp>
//#include <math/color.hpp>

namespace Neb {
	namespace glsl {
		class program;

		namespace Uniform {
			namespace Scalar {
				/** @brief %Base
				 *
				 * base class for scalar GLSL uniform
				 */
				class Base {
					public:
						Base(std::string);
						virtual ~Base() {}
						void			locate(std::shared_ptr<program>);
						/** @name Load
						 * @{
						 */
						virtual void			load(vec3 const &) { throw 0; }
						virtual void			load(vec4 const &) { throw 0; }
						virtual void			load(mat4 const &) { throw 0; }
						//virtual void			load(math::Color::color<float>) { throw 0; }
						//virtual void			load(math::Color::color<double>) { throw 0; }
						virtual void			load(int) { throw 0; }
						virtual void			load(float*) { throw 0; }
						virtual void			load(double*) { throw 0; }
						virtual void			load(float) { throw 0; }
						virtual void			load(double) { throw 0; }
						/** @} */
					protected:
						std::string		name_;
						GLint			o_;
				};

				class Int: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Int(std::string s): Base(s) {}
						virtual void		load(int);
				};
				class Float: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Float(std::string s): Base(s) {}
						virtual void		load(float);
				};
				class Double: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Double(std::string s): Base(s) {}
						virtual void		load(double);
				};
				class Vec3: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Vec3(std::string s): Base(s) {}
						virtual void		load(vec3 const &);
						virtual void		load(float*);
				};
				class Vec4: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Vec4(std::string s): Base(s) {}
						virtual void		load(float*);
				};
				class DVec4: public Neb::glsl::Uniform::Scalar::Base {
					public:
						DVec4(std::string s): Base(s) {}
						virtual void		load(double*);
				};
				class Mat4: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Mat4(std::string s): Base(s) {}
						virtual void		load(mat4 const &);
				};
				class Sampler2D: public Neb::glsl::Uniform::Scalar::Base {
					public:
						Sampler2D(std::string s): Base(s) {}
						virtual void		load(int);
				};
			}
		}
	}
}
#endif









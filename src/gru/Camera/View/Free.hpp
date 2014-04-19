#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <math/vec3.hpp>

#include <galaxy/sig/connection.hpp>

namespace glutpp {
	/*class camera_control {
	  public:
	  virtual math::mat44		supply() = 0;
	  double				last_;
	  };*/
	namespace Camera {
		namespace View {
			/** @brief free flying camera
			 * this camera can move freely through the scene
			 * user input in interpreted as three-component velocity and yaw and pitch rate
			 */
			class Free: public Base {
				public:
					/** @name constructors
					 * @{
					 */
					Free();
					Free(math::vec3<double> eye, double yaw, double pitch);
					/** @} */

					virtual math::mat44			view();

					void					init(glutpp::window::window_s);

					int					callback_x_(int,float);
					int					callback_y_(int,float);
					int					callback_z_(int,float);

					void					step(double);

					float					pitch_;
					float					yaw_;



					math::vec4					eye_;
					math::vec3<double>				center_;
					math::vec3<double>				look_;
					math::vec3<double>				up_;

					math::vec3<double>				v0_;
					math::vec3<double>				v1_;

					std::vector<gal::sig::connection<>*>		vec_x_;
					std::vector<gal::sig::connection<>*>		vec_y_;
					std::vector<gal::sig::connection<>*>		vec_z_;

					glutpp::window::window_w				window_;
			};
		}
	}
}
#endif




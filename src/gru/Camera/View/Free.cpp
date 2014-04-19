
#include <gru/config.hpp>
#include <gru/window/window.hpp>
#include <gru/Camera/View/Free.hpp>

glutpp::Camera::View::Free::Free():
	eye_(0.0f, 0.0f, 5.0f, 0.0f),
	center_(0.0f,0.0f,0.0f),
	up_(0.0f,1.0f,0.0f)
{}
void	glutpp::Camera::View::Free::init(glutpp::window::window_s window)
{
	window_ = window;
/*
	vec_x_.push_back(
			window_->map_sig_key_down_['d'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 0, 1.0)));

	vec_x_.push_back(
			window_->map_sig_key_up_['d'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 0, 0.0)));

	vec_x_.push_back(
			window_->map_sig_key_down_['a'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 1, -1.0)));

	vec_x_.push_back(
			window_->map_sig_key_up_['a'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 1, 0.0)));

	vec_y_.push_back(
			window_->map_sig_key_down_['e'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 0, 1.0)));

	vec_y_.push_back(
			window_->map_sig_key_up_['e'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 0, 0.0)));

	vec_y_.push_back(
			window_->map_sig_key_down_['c'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 1, -1.0)));

	vec_y_.push_back(
			window_->map_sig_key_up_['c'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 1, 0.0)));

	vec_z_.push_back(
			window_->map_sig_key_down_['w'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 0, -1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['w'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 0, 0.0)));

	vec_z_.push_back(
			window_->map_sig_key_down_['s'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 1, 1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['s'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 1, 0.0)));
*/

}
int	glutpp::Camera::View::Free::callback_x_(int a, float s) {
	/** TODO better system for turning key up/down into simple movement */

	if(a==0) v0_.x() = s;
	if(a==1) v1_.x() = s;

	return 1;
}
int	glutpp::Camera::View::Free::callback_y_(int a, float s) {
	if(a==0) v0_.y() = s;
	if(a==1) v1_.y() = s;

	return 1;
}
int	glutpp::Camera::View::Free::callback_z_(int a, float s) {
	if(a==0) v0_.z() = s;
	if(a==1) v1_.z() = s;

	return 1;
}
void	glutpp::Camera::View::Free::step(double time) {
	double dt = time - last_; last_ = time;

	// look vector
	math::vec3<double> look = center_ - eye_;

	// project to xz-plane
	look.y() = 0.0;
	look.Normalize();

	math::vec3<double> x(1,0,0);
	math::vec3<double> y(0,1,0);
	math::vec3<double> z(0,0,-1);

	math::vec3<double> c = z.cross(look);

	float yaw = asin(c.magnitude());

	float d = y.dot(c);
	float e = z.dot(look);

	if(e < 0) yaw = M_PI - yaw;


	yaw *= (d > 0) ? 1.0 : -1.0;


	printf("yaw = %f\n",yaw);

	// rotate velocity by camera yaw
	math::quat q(yaw,y);


	math::vec3<double> v = v0_ + v1_;
	v *= dt;
	v *= 4.0;

	v = q.rotate(v);

	eye_ += math::vec4(v, 0.0f);
}


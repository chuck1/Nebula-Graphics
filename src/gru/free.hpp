#ifndef GRU_FREE_HPP
#define GRU_FREE_HPP

#include <memory>

#include <gru/Graphics/Color/Color.hpp>

namespace glutpp {
	void	draw_quad(float, float, float, float, gru::Color::color<float>);
	void	draw_text(float, float, float, float, gru::Color::color<float>, std::string);
}

void	checkerror(char const *);
bool	isGLError();

template<class A> A*	new_copy(std::shared_ptr<A> a) {
	if(a) {
		return new A(*a);
	}
       	return NULL;
}

#endif

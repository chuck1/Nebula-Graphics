#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>


#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <glutpp/camera.h>
#include <glutpp/light.h>
#include <glutpp/master.h>


namespace glutpp
{
	class window
	{
		protected:

			int          windowID;

		public:
			window(int, int, int, int, const char * );
			~window();

			int			height;
			int			width;
			int			initPositionX;
			int			initPositionY;


			void			StartSpinning();
			void			CallBackDisplayFunc();
			void			CallBackIdleFunc(void);


			virtual void		CallBackKeyboardFunc(unsigned char key, int x, int y);
			virtual void		CallBackMotionFunc(int x, int y);
			virtual void		CallBackMouseFunc(int button, int state, int x, int y);
			virtual void		CallBackPassiveMotionFunc(int x, int y);
			virtual void		CallBackReshapeFunc(int w, int h);   
			virtual void		CallBackSpecialFunc(int key, int x, int y);   
			virtual void		CallBackVisibilityFunc(int visible);


			void			Reshape();

			void			SetWindowID(int newWindowID);
			int			GetWindowID(void);
			
			
			virtual void		Display();
			virtual void		DisplayOrtho();
			virtual void		Idle();


			//math::mat44		lightProjectionMatrix;
			//math::mat44		lightViewMatrix;
			//math::mat44		cameraProjectionMatrix;
			//math::mat44		cameraViewMatrix;
			
			camera			cam;
			light			lit;

			void	update_camera_matrix(math::vec3 eye,math::vec3 center, math::vec3 up);
			void	update_light_matrix();

	};
}

#endif








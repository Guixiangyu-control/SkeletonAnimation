#ifndef __TEMPLATE_APP_HEADER_H__
#define __TEMPLATE_APP_HEADER_H__

#include "OpenGLApp.h"

class Mesh;

/** Class */
class model_loader_app : public OpenGLApp
{
public:
	/** ��ʼ������.
	@remarks
		����ĳ�ʼ��.
	*/
	void init();

	/// OpenGL ������ʼ��
	void startup();

	/// OpenGL ��������
	void shutdown();

	virtual void onKey(int key, int scancode, int action, int mods);

	/// ��Ⱦ
	void render(double t);

private:
	GLuint      program;		/// �������
	GLuint		skeletonProgram;
	GLuint      vao;			/// �����������
	GLuint		proj_location;
	GLuint		mv_location;
	GLuint		light_location;
	GLuint		tex1_location;
	GLuint		tex2_location;
	GLuint		tex3_location;
	GLuint		skeleton_mv_location;
	GLuint		skeleton_proj_location;
	GLuint		skeleton_bonemat_location;

	Mesh*		mMesh;
};


#endif
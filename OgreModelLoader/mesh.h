#ifndef __MESH_H__
#define __MESH_H__

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "MeshAnimation.h"

class Mesh
{
public:
	// ---------------------------------------- //
	// Structures
	// ---------------------------------------- //
	struct Triangle
	{
		int index[3];	// vertex    ID
		int material;	// material  ID
	};

	struct SubEntityInfo
	{
		int start;
		int count;
		int material;
	};
	// ---------------------------------------- //
	class Vertex
	{
	public: 

		// general
		glm::vec3 position;
		glm::vec3 texcoord;
		glm::vec3 normal;
		glm::vec4 tangent;

		// skinning information
		float weight[3];
		int boneindex[3],count;

		// initialization
		Vertex()
		{
			count=0;
			weight[0]=weight[1]=weight[2]=0;
			boneindex[0]=boneindex[1]=boneindex[2]=0;
		};
	};
	// ---------------------------------------- //
	class Texture
	{
	public:
		Texture(){envmap=0;gl_handle=-1;}

		std::string filename;
		int gl_handle;
		bool envmap;
	};
	// ---------------------------------------- //
	class Material
	{
	public:

		Material()
		{
			ambient = glm::vec3( 0.6 , 0.3 ,0 );
			diffuse = glm::vec3( 0.3 , 0.3 ,0.3 );
			specular= glm::vec3( 0,0,0 );
			emissive= glm::vec3( 0,0,0 );
			diffuse_map.gl_handle=-1;
			emissive_map.gl_handle=-1;
			ambient_map.gl_handle=-1;
			alpha = 1;
			reflect = 0;
			name = "";
		}
		std::string name;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 ambient;
		glm::vec3 emissive;
		float alpha,reflect;
		Texture diffuse_map;
		Texture emissive_map;
		Texture ambient_map;
		Texture bump_map;
	};
	
	// ---------------------------------------- //
	struct LOD // level of detail mesh
	{
		std::vector<Triangle>		triangles;
		std::vector<SubEntityInfo> m_subEntity;
		unsigned int start;	// ��������ʼλ��
	};

	struct VertexInfo
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texcoord;
		glm::vec3 weights;
	};

	// ---------------------------------------- //
	// Main OBJ Part
	// ---------------------------------------- //
	

	/** ���캯��. */
	Mesh();
	/** ���캯��. */
	~Mesh();

	/** �ı䵱ǰ����.. */
	void changeAnim();
	void changeLod();
	void changePaused() { mbPause = !mbPause; }

	/** ���캯��. */
	Mesh(char* ogrematerialfilename, char* ogremeshfilenamexml, unsigned int program, char* ogreskeletonfilenamexml=0);
	Mesh(char* tlbbobjectfilename, unsigned int program);

	void draw(double t, unsigned int program = 0, bool bSkeleton = false);	/// ����.
	glm::vec3 getViewPos() { return mViewPos; }
	glm::vec3 getSize() { return mMaxPos - mMinPos; }
private:
	void init();		/// ��ʼ��
	void LoadOgreXML(const char* name_material, const char* name_mesh);	/// ���� �����ļ���mesh�ļ�
	void LoadMesh(const char* name_mesh);
	void LoadObjXML(char* name_object);
	int GetMaterialIndex ( std::string name );		/// �õ���������
	void PrintMaterials ();			/// ��ӡ����
	void buildGeometry();			/// ����������
	void updateMin(glm::vec3 v) 
	{ mMinPos.x = glm::min<float>(mMinPos.x, v.x); mMinPos.y = glm::min<float>(mMinPos.y, v.y); mMinPos.z = glm::min<float>(mMinPos.z, v.z); }
	void updateMax(glm::vec3 v) 
	{ mMaxPos.x = glm::max<float>(mMaxPos.x, v.x); mMaxPos.y = glm::max<float>(mMaxPos.y, v.y); mMaxPos.z = glm::max<float>(mMaxPos.z, v.z); }

	unsigned int mVAO;				/// ��ģ�͵� VAO
	unsigned int mBuffer;			/// ���� buffer
	unsigned int mSkeletonBuffer;
	unsigned int mSkeletonIndexBuffer;
	unsigned int mBoneBuffer;		/// �������� buffer
	unsigned int mIndexBuffer;		/// ���� buffer
	unsigned int mProgram;			/// ��ǰ�������
	unsigned int mCubeVAO;

	unsigned int mSkinLoc;
	unsigned int mBoneMatLoc;


	int mAnimIndex;			/// ��ǰ����������
	double mAnimTime;		/// ��ǰ�����Ĳ���ʱ��
	bool mbSkin;			/// �Ƿ�ʹ�ö���
	double mAnimLength;		/// ��ǰ�����ĳ���
	double mbPause;

	bool					skinning;	// skinning on ?
	std::vector<LOD>		lod_meshes;	// triangles & displaylists for all LODs
	std::vector<Vertex>		vertices;	// vertex list
	std::vector<Material>	materials;	// material list
	int mCurrentLod;

	//GLuint mBoneBuffer;

	struct ObjectSubEntity
	{
		std::vector<LOD> lod_meshes;
		std::vector<Vertex> vertices;
		std::vector<Material> materials;
	};
	
	glm::vec3 mMinPos;
	glm::vec3 mMaxPos;
	glm::vec3 mViewPos;

	MeshAnimation mAnimation;		/// ���涯������.
};

#endif
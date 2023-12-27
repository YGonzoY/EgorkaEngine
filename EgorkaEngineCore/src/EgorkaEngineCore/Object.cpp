#include "EgorkaEngineCore/Object.hpp"


namespace EgorkaEngine
{
	Object::Object(GLfloat* _positions_normals_uvs, GLuint* _indexes, std::unique_ptr<Texture2D>* _textures)
	{
		positions_normals_uvs = _positions_normals_uvs;
		indexes = _indexes;

	}
}
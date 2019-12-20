#include "hzpch.h"

#include "Mesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace Hazel {
	
	Mesh::Mesh(const std::string& path) {
		HZ_PROFILE_FUNCTION();
		Assimp::Importer Importer;
		const aiScene* scene = Importer.ReadFile(path.c_str(), aiProcess_Triangulate|aiProcess_GenSmoothNormals|aiProcess_FlipUVs|aiProcess_JoinIdenticalVertices);
		
		HZ_CORE_ASSERT(scene, "Failed To Load Model @ '{0}'", path);
	
		HZ_CORE_ASSERT(scene->HasMeshes(), "No Meshes In {0}", path);
		HZ_CORE_ASSERT(scene->mNumMeshes == 1, "More Than 1 Mesh in {0}", path);
		auto *currentMesh = scene->mMeshes[0];
		
		for (uint32_t i = 0; i < currentMesh->mNumVertices; i++) {
			aiVector3D vertex = currentMesh->mVertices[i];
			aiVector3D normal = currentMesh->mNormals[i];
			aiVector3D texCoord = currentMesh->HasTextureCoords(0) ? currentMesh->mTextureCoords[0][i] : aiVector3D{0.f, 0.f, 0.f};

			m_Vertices.emplace_back(vertex.x, vertex.y, vertex.z);
			m_Normals.emplace_back(normal.x, normal.y, normal.z);
			m_TexCoords.emplace_back(texCoord.x, texCoord.y);
		}
		for (uint32_t i = 0; i < currentMesh->mNumFaces; i++) {
			aiFace face = currentMesh->mFaces[i];
			HZ_CORE_ASSERT(face.mNumIndices== 3, "More Than Three Indices in '{0}' Mesh", path);
			
			for (int j = 0; j < 3; j++) {
				m_Indices.emplace_back(face.mIndices[j]);
			}
		}
	}

}
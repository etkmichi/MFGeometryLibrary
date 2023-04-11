/*
 * MFVkVertexDataOptimizer.h
 *
 *  Created on: 03.12.2019
 *      Author: michl
 */

#ifndef MFVERTEXCLASSES_MFVERTEXDATAOPTIMIZER_H_
#define MFVERTEXCLASSES_MFVERTEXDATAOPTIMIZER_H_
#include <vector>
#include <mutex>
#include <glm/glm.hpp>
/**
 * This class provides mechanism for calculating geometry and rendering related data
 * for triangles.
 */
class MFVertexDataOptimizer {
private:
	static std::mutex
		lockVec256Normals,
		lockVec256NormalsWrite;

	static std::vector<glm::vec3>
		*ms_vec256Normals;
public:
	MFVertexDataOptimizer();
	virtual ~MFVertexDataOptimizer();

	std::vector<uint8_t >* calc8BitIndexedNormals (std::vector<glm::vec3>* normals);
	std::vector<uint16_t>* calc16BitIndexedNormals(std::vector<glm::vec3>* normals);
	std::vector<uint32_t>* calc32BitIndexedNormals(std::vector<glm::vec3>* normals);
	/**
	 * This function calculates normals for each vertex. Take care this calculation
	 * takes a lot of time. The normal of a vertex is calculated by its cornering
	 * triangles. The algorithm uses a lot of time for searching! If the vertices are
	 * a subpart of a collection defining one structure, the normals of each border
	 * are calculated wrong, because the neighboring triangles are not available in
	 * the vertices pointer.
	 *
	 * @param vertices
	 * @param indices
	 * @return
	 */
	bool calcVertexNormals(
			const std::vector<glm::vec3>* pVertices,
			const std::vector<uint32_t>* pIndices,
			std::vector<glm::vec3>* pVecVertexNormals
			);

	/**
	 * Sets the normals which will be used for indexd normals calculation
	 * @param vec256Normals
	 */
	static void set256NormalsVector(std::vector<glm::vec3> *vec256Normals){ms_vec256Normals=vec256Normals;};
	static std::vector<glm::vec3>* get256NormalsVector(){return ms_vec256Normals;};
	static bool create256NormalsVector();
	/**
	 * The normalse are calculated in 16 point circles from vec(0,0,-1) to vec(0,0,1).
	 * To optimize the search for a specific normal, this funciton can be used to get
	 * a close lower index into the 256 (count of normals) normals vector
	 * @param zCoordinate
	 * @return
	 */
	static uint32_t getCloseLowerIndexFor256Normals(float zCoordinate);
	static uint8_t get8BitNormalIndex(glm::vec3 normal);
	static void print256NormalsVector();
};

#endif /* MFVERTEXCLASSES_MFVERTEXDATAOPTIMIZER_H_ */

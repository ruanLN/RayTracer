#include "objloader.h"


#include <stdio.h>
#include <string>
#include <cstring>


// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(
	const char * path,
    std::vector<Point3D> & out_vertices,
    std::vector<std::pair<float, float> > & out_uvs,
    std::vector<Vector3D> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Point3D> temp_vertices;
    std::vector<std::pair<float, float> > temp_uvs;
    std::vector<Vector3D> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
            double x, y, z;
            fscanf(file, "%lf %lf %lf\n", &x, &y, &z );
            Point3D vertex(x, y, z);
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
            std::pair<double, double> uv;
            fscanf(file, "%lf %lf\n", &uv.first, &uv.second );
            uv.second = -uv.second; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
            double x, y, z;
            fscanf(file, "%lf %lf %lf\n", &x, &y, &z );
            Vector3D normal(x, y, z);

			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
            int v, t, n;
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            char face[50];
            fgets(face, 50, file);
            //scan the variations of face: %d %d %d, %d//%d, %d/%d, %d/%d/%d
            char *vertex;
            int i = 0;
            if(strstr(vertex, "//") != NULL) {  // %d//%d
                int v, n;
                sscanf(vertex, "%d//%d", &v, &n);
                vertexIndices.push_back(v);
                normalIndices.push_back(n);
                sscanf(vertex, "%d//%d", &v, &n);
                vertexIndices.push_back(v);
                normalIndices.push_back(n);
                sscanf(vertex, "%d//%d", &v, &n);
                vertexIndices.push_back(v);
                normalIndices.push_back(n);

                while(fscanf(file, "%d//%d", &v, &n) > 0) {
                    int vindex = vertexIndices.size() -1;   //last element
                    int nindex = normalIndices.size() -1;
                    vertexIndices.push_back(vertexIndices[vindex-2]);
                    normalIndices.push_back(normalIndices[nindex-2]);
                    vertexIndices.push_back(vertexIndices[vindex]);
                    normalIndices.push_back(normalIndices[nindex]);
                    vertexIndices.push_back(v);
                    normalIndices.push_back(n);
                }
            } else if (fscanf(file, "%d/%d/%d", &v, &t, &n) == 3) {  // %d/%d/%d
                /* v/t/n */
                int v, t, n;
                vertexIndices.push_back(v);
                uvIndices.push_back(t);
                normalIndices.push_back(n);
                fscanf(file, "%d/%d/%d", &v, &t, &n);
                vertexIndices.push_back(v);
                uvIndices.push_back(t);
                normalIndices.push_back(n);
                fscanf(file, "%d/%d/%d", &v, &t, &n);
                vertexIndices.push_back(v);
                uvIndices.push_back(t);
                normalIndices.push_back(n);

                while(fscanf(file, "%d/%d/%d", &v, &t, &n) > 0) {
                    //if (n== 181228)   //<- why?
                    int vindex = vertexIndices.size() -1;   //last element
                    int tindex = uvIndices.size() -1;
                    int nindex = normalIndices.size() -1;
                    vertexIndices.push_back(vertexIndices[vindex-2]);
                    uvIndices.push_back(uvIndices[tindex-2]);
                    normalIndices.push_back(normalIndices[nindex-2]);
                    vertexIndices.push_back(vertexIndices[vindex]);
                    uvIndices.push_back(uvIndices[tindex]);
                    normalIndices.push_back(normalIndices[nindex]);
                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                    normalIndices.push_back(n);

                }
            } else if (fscanf(file, "%d/%d", &v, &t) == 2) {
                /* v/t */
                int v, t;

                vertexIndices.push_back(v);
                uvIndices.push_back(t);
                fscanf(file, "%d/%d", &v, &t);
                vertexIndices.push_back(v);
                uvIndices.push_back(t);
                fscanf(file, "%d/%d", &v, &t);
                vertexIndices.push_back(v);
                uvIndices.push_back(t);

                while(fscanf(file, "%d/%d", &v, &t) > 0) {
                    //if (n== 181228)   //<- why?
                    int vindex = vertexIndices.size() -1;   //last element
                    int tindex = uvIndices.size() -1;
                    vertexIndices.push_back(vertexIndices[vindex-2]);
                    uvIndices.push_back(uvIndices[tindex-2]);
                    vertexIndices.push_back(vertexIndices[vindex]);
                    uvIndices.push_back(uvIndices[tindex]);;
                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);

                }
            } else {
                /* v/t */
                int v;
                fscanf(file, "%d", &v);
                vertexIndices.push_back(v);
                fscanf(file, "%d", &v);
                vertexIndices.push_back(v);
                fscanf(file, "%d", &v);
                vertexIndices.push_back(v);

                while(fscanf(file, "%d", &v) > 0) {
                    //if (n== 181228)   //<- why?
                    int vindex = vertexIndices.size() -1;   //last element
                    vertexIndices.push_back(vertexIndices[vindex-2]);
                    vertexIndices.push_back(vertexIndices[vindex]);
                    vertexIndices.push_back(v);

                }
            }

            //int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
            //if (matches != 3){
            //	printf("File can't be read by our simple parser :-( Try exporting with other options\n");
            //	return false;
            //}
            //vertexIndices.push_back(vertexIndex[0]);
            //vertexIndices.push_back(vertexIndex[1]);
            //vertexIndices.push_back(vertexIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];

		// Get the attributes thanks to the index
        Point3D vertex = temp_vertices[ vertexIndex-1 ];
        //std::pair<float, float> uv = temp_uvs[ uvIndex-1 ];
        //Vector3D normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
        out_vertices.push_back(vertex);
        //out_uvs     .push_back(uv);
        //out_normals .push_back(normal);

	}
    // For each normal of each triangle
    for( unsigned int i=0; i<normalIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        //Point3D vertex = temp_vertices[ vertexIndex-1 ];
        //std::pair<float, float> uv = temp_uvs[ uvIndex-1 ];
        Vector3D normal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        //out_vertices.push_back(vertex);
        //out_uvs     .push_back(uv);
        out_normals .push_back(normal);

    }
    for( unsigned int i=0; i<uvIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int uvIndex = uvIndices[i];

        // Get the attributes thanks to the index
        //Point3D vertex = temp_vertices[ vertexIndex-1 ];
        std::pair<float, float> uv = temp_uvs[ uvIndex-1 ];
        //Vector3D normal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        //out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
        //out_normals .push_back(normal);

    }

	return true;
}

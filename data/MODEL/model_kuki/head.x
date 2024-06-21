xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 126;
 0.00000;0.00000;0.00000;,
 18.07325;0.09109;-0.00000;,
 18.07325;0.06702;-0.00000;,
 0.00000;0.06702;0.00000;,
 35.65123;0.07461;-0.00000;,
 35.65123;0.06702;-0.00000;,
 18.07325;15.29089;-0.00000;,
 0.00000;0.07190;0.00000;,
 35.65123;0.04302;-0.00000;,
 35.65123;0.07461;-0.00000;,
 35.65123;0.07461;-0.06432;,
 35.65123;0.06702;-0.06432;,
 35.65123;0.06702;-0.00000;,
 35.65123;0.04302;-0.06432;,
 35.65123;0.04302;-0.00000;,
 35.65123;0.07461;-0.06432;,
 18.07325;0.29250;-0.06432;,
 18.07325;0.06702;-33.32823;,
 35.65123;0.06702;-0.06432;,
 0.00000;0.00000;-0.06432;,
 0.00000;0.06702;-0.06432;,
 18.07325;15.29089;-0.06432;,
 35.65123;0.04302;-0.06432;,
 0.00000;0.07190;-0.06432;,
 0.00000;0.00000;-0.06432;,
 0.00000;0.00000;0.00000;,
 0.00000;0.06702;0.00000;,
 0.00000;0.06702;-0.06432;,
 0.00000;0.07190;0.00000;,
 0.00000;0.07190;-0.06432;,
 18.07325;0.09109;-0.00000;,
 0.00000;0.00000;0.00000;,
 35.65123;0.07461;-0.00000;,
 0.00000;0.07190;0.00000;,
 18.07325;15.29089;-0.00000;,
 35.65123;0.04302;-0.00000;,
 17.53565;5.96084;-8.60986;,
 13.62778;4.81997;-7.44087;,
 17.53565;4.81997;-5.55888;,
 17.53565;5.96084;-8.60986;,
 12.66259;4.81997;-9.72211;,
 17.53565;5.96084;-8.60986;,
 15.36691;4.81997;-11.50503;,
 17.53565;5.96084;-8.60986;,
 19.70439;4.81997;-11.50503;,
 17.53565;5.96084;-8.60986;,
 22.40871;4.81997;-9.72211;,
 17.53565;5.96084;-8.60986;,
 21.44352;4.81997;-7.44087;,
 17.53565;5.96084;-8.60986;,
 17.53565;4.81997;-5.55888;,
 10.49395;1.62334;-4.94170;,
 17.53565;1.62334;-1.55059;,
 8.75472;1.62334;-10.61405;,
 13.62778;1.62334;-15.11645;,
 21.44352;1.62334;-15.11645;,
 26.31658;1.62334;-10.61405;,
 24.57735;1.62334;-4.94170;,
 17.53565;1.62334;-1.55059;,
 8.75472;-2.99578;-3.55479;,
 17.53565;-2.99578;0.67392;,
 6.58608;-2.99578;-11.10903;,
 12.66259;-2.99578;-17.12055;,
 22.40871;-2.99578;-17.12055;,
 28.48522;-2.99578;-11.10903;,
 26.31658;-2.99578;-3.55479;,
 17.53565;-2.99578;0.67392;,
 8.75472;-8.12266;-3.55479;,
 17.53565;-8.12266;0.67392;,
 6.58608;-8.12266;-11.10903;,
 12.66259;-8.12266;-17.12055;,
 22.40871;-8.12266;-17.12055;,
 28.48522;-8.12266;-11.10903;,
 26.31658;-8.12266;-3.55479;,
 17.53565;-8.12266;0.67392;,
 10.49395;-12.74177;-4.94170;,
 17.53565;-12.74177;-1.55059;,
 8.75472;-12.74177;-10.61405;,
 13.62778;-12.74177;-15.11645;,
 21.44352;-12.74177;-15.11645;,
 26.31658;-12.74177;-10.61405;,
 24.57735;-12.74177;-4.94170;,
 17.53565;-12.74177;-1.55059;,
 13.62778;-15.93838;-7.44087;,
 17.53565;-15.93838;-5.55898;,
 12.66259;-15.93838;-9.72211;,
 15.36691;-15.93838;-11.50503;,
 19.70439;-15.93838;-11.50503;,
 22.40871;-15.93838;-9.72211;,
 21.44352;-15.93838;-7.44087;,
 17.53565;-15.93838;-5.55898;,
 17.53565;-17.07913;-8.60986;,
 17.53565;-17.07913;-8.60986;,
 17.53565;-17.07913;-8.60986;,
 17.53565;-17.07913;-8.60986;,
 17.53565;-17.07913;-8.60986;,
 17.53565;-17.07913;-8.60986;,
 17.53565;-17.07913;-8.60986;,
 29.42516;0.23550;0.98784;,
 29.42516;-17.21470;0.98784;,
 29.42515;-17.21470;-14.27607;,
 29.42515;0.23550;-14.27607;,
 29.42515;-0.19133;-14.18996;,
 29.42515;-17.22815;-14.18996;,
 29.42516;-17.22815;0.98784;,
 29.42516;-0.19133;0.98784;,
 6.12576;-0.19133;0.98784;,
 6.12576;-17.22815;0.98784;,
 6.12576;-17.22815;-13.90099;,
 6.12576;-0.19133;-13.90099;,
 6.12576;-0.19133;-13.81200;,
 6.12576;-17.22815;-13.81200;,
 6.12576;-17.22815;0.98784;,
 6.12576;-0.19133;0.98784;,
 18.04397;-7.93284;-19.94765;,
 18.04397;-17.23477;-19.94765;,
 6.04618;-17.23477;-13.96887;,
 6.04618;-7.93284;-13.96887;,
 29.41863;-7.93284;-14.17824;,
 29.41863;-17.33787;-14.17824;,
 17.83565;-17.33787;-20.00765;,
 17.83565;-7.93284;-20.00765;,
 6.13546;0.23550;0.84806;,
 6.13546;-16.80132;0.84806;,
 29.34740;-16.80132;0.84806;,
 29.34740;0.23550;0.84806;;
 
 72;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;12,11,13,14;,
 4;15,16,17,18;,
 4;16,19,20,17;,
 4;18,17,21,22;,
 4;17,20,23,21;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;24,16,30,31;,
 4;16,10,32,30;,
 4;33,34,21,29;,
 4;34,35,13,21;,
 3;36,37,38;,
 3;39,40,37;,
 3;41,42,40;,
 3;43,44,42;,
 3;45,46,44;,
 3;47,48,46;,
 3;49,50,48;,
 4;38,37,51,52;,
 4;37,40,53,51;,
 4;40,42,54,53;,
 4;42,44,55,54;,
 4;44,46,56,55;,
 4;46,48,57,56;,
 4;48,50,58,57;,
 4;52,51,59,60;,
 4;51,53,61,59;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,57,65,64;,
 4;57,58,66,65;,
 4;60,59,67,68;,
 4;59,61,69,67;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,65,73,72;,
 4;65,66,74,73;,
 4;68,67,75,76;,
 4;67,69,77,75;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,73,81,80;,
 4;73,74,82,81;,
 4;76,75,83,84;,
 4;75,77,85,83;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,81,89,88;,
 4;81,82,90,89;,
 3;84,83,91;,
 3;83,85,92;,
 3;85,86,93;,
 3;86,87,94;,
 3;87,88,95;,
 3;88,89,96;,
 3;89,90,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;;
 
 MeshMaterialList {
  7;
  72;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  6,
  6,
  1,
  1,
  1,
  1;;
  Material {
   0.432800;0.432800;0.432800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.068800;0.068800;0.068800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.677600;0.652800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.040800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.354400;0.354400;0.354400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  76;
  0.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.001635;-0.452862;-0.891579;,
  0.000000;0.000000;-1.000000;,
  -0.902640;-0.388912;0.184361;,
  -0.629517;-0.702095;0.332822;,
  -0.959009;-0.256061;0.121383;,
  -1.000000;0.000000;0.000000;,
  0.623892;0.719741;0.304518;,
  0.007531;-0.760651;-0.649117;,
  0.008851;-0.709444;-0.704706;,
  -0.892707;0.421328;-0.159865;,
  -0.000000;0.999988;0.004863;,
  0.000000;0.871173;0.490976;,
  -0.342907;0.879474;0.330061;,
  -0.385862;0.915001;-0.117827;,
  -0.148434;0.873159;-0.464286;,
  0.148434;0.873159;-0.464286;,
  0.385862;0.915001;-0.117827;,
  0.342908;0.879474;0.330061;,
  0.000000;0.627323;0.778759;,
  -0.589861;0.621379;0.515706;,
  -0.726362;0.657815;-0.199192;,
  -0.279080;0.613797;-0.738490;,
  0.279080;0.613797;-0.738490;,
  0.726362;0.657815;-0.199192;,
  0.589861;0.621378;0.515707;,
  0.000000;0.224532;0.974467;,
  -0.743931;0.221817;0.630368;,
  -0.939813;0.235485;-0.247587;,
  -0.367373;0.218509;-0.904042;,
  0.367373;0.218509;-0.904042;,
  0.939813;0.235485;-0.247587;,
  0.743932;0.221817;0.630368;,
  0.000000;-0.224532;0.974467;,
  -0.743931;-0.221817;0.630368;,
  -0.939873;-0.203641;0.274169;,
  -0.367373;-0.218509;-0.904042;,
  0.367373;-0.218509;-0.904041;,
  0.683001;-0.202992;-0.701644;,
  0.743932;-0.221817;0.630368;,
  0.000000;-0.627325;0.778757;,
  -0.589858;-0.621381;0.515706;,
  -0.726361;-0.657816;-0.199192;,
  -0.279080;-0.613798;-0.738489;,
  0.279079;-0.613798;-0.738489;,
  0.726361;-0.657816;-0.199192;,
  0.589858;-0.621381;0.515706;,
  0.000000;-0.871181;0.490962;,
  -0.342894;-0.879483;0.330052;,
  -0.385850;-0.915007;-0.117823;,
  -0.148430;-0.873168;-0.464271;,
  0.148430;-0.873168;-0.464271;,
  0.385850;-0.915007;-0.117823;,
  0.342894;-0.879483;0.330052;,
  -0.000000;-0.999988;0.004866;,
  1.000000;0.000000;-0.000000;,
  0.001199;-0.595342;-0.803471;,
  0.004045;-0.776809;-0.629724;,
  0.533258;0.615717;0.580110;,
  -0.808154;0.392470;-0.439151;,
  -0.978705;0.136785;-0.153054;,
  -0.761040;0.606513;-0.230130;,
  -0.906676;0.421829;0.000000;,
  0.006169;-0.807511;-0.589820;,
  -0.002915;-0.807525;-0.589826;,
  -0.644121;0.764923;0.000000;,
  0.655265;0.755399;0.000000;,
  -0.683001;-0.202992;-0.701644;,
  0.939873;-0.203641;0.274169;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.446013;0.000000;-0.895027;,
  0.449552;0.000000;-0.893254;,
  0.000000;-0.000000;1.000000;;
  72;
  4;0,0,0,0;,
  4;57,2,3,3;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;7,4,6,7;,
  4;7,6,7,7;,
  4;4,5,5,6;,
  4;58,9,10,10;,
  4;59,59,8,8;,
  4;60,61,11,62;,
  4;7,7,7,61;,
  4;61,7,63,11;,
  4;9,58,57,64;,
  4;58,65,2,57;,
  4;63,66,62,11;,
  4;67,67,8,8;,
  3;12,14,13;,
  3;12,15,14;,
  3;12,16,15;,
  3;12,17,16;,
  3;12,18,17;,
  3;12,19,18;,
  3;12,13,19;,
  4;13,14,21,20;,
  4;14,15,22,21;,
  4;15,16,23,22;,
  4;16,17,24,23;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,13,20,26;,
  4;20,21,28,27;,
  4;21,22,29,28;,
  4;22,23,30,29;,
  4;23,24,31,30;,
  4;24,25,32,31;,
  4;25,26,33,32;,
  4;26,20,27,33;,
  4;27,28,35,34;,
  4;28,29,36,35;,
  4;29,30,37,68;,
  4;30,31,38,37;,
  4;31,32,39,38;,
  4;32,33,40,69;,
  4;33,27,34,40;,
  4;34,35,42,41;,
  4;35,36,43,42;,
  4;68,37,44,43;,
  4;37,38,45,44;,
  4;38,39,46,45;,
  4;69,40,47,46;,
  4;40,34,41,47;,
  4;41,42,49,48;,
  4;42,43,50,49;,
  4;43,44,51,50;,
  4;44,45,52,51;,
  4;45,46,53,52;,
  4;46,47,54,53;,
  4;47,41,48,54;,
  3;48,49,55;,
  3;49,50,55;,
  3;50,51,55;,
  3;51,52,55;,
  3;52,53,55;,
  3;53,54,55;,
  3;54,48,55;,
  4;56,56,56,56;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;;
 }
 MeshTextureCoords {
  126;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.071430;0.000000;,
  0.142860;0.142860;,
  0.000000;0.142860;,
  0.214290;0.000000;,
  0.285710;0.142860;,
  0.357140;0.000000;,
  0.428570;0.142860;,
  0.500000;0.000000;,
  0.571430;0.142860;,
  0.642860;0.000000;,
  0.714290;0.142860;,
  0.785710;0.000000;,
  0.857140;0.142860;,
  0.928570;0.000000;,
  1.000000;0.142860;,
  0.142860;0.285710;,
  0.000000;0.285710;,
  0.285710;0.285710;,
  0.428570;0.285710;,
  0.571430;0.285710;,
  0.714290;0.285710;,
  0.857140;0.285710;,
  1.000000;0.285710;,
  0.142860;0.428570;,
  0.000000;0.428570;,
  0.285710;0.428570;,
  0.428570;0.428570;,
  0.571430;0.428570;,
  0.714290;0.428570;,
  0.857140;0.428570;,
  1.000000;0.428570;,
  0.142860;0.571430;,
  0.000000;0.571430;,
  0.285710;0.571430;,
  0.428570;0.571430;,
  0.571430;0.571430;,
  0.714290;0.571430;,
  0.857140;0.571430;,
  1.000000;0.571430;,
  0.142860;0.714290;,
  0.000000;0.714290;,
  0.285710;0.714290;,
  0.428570;0.714290;,
  0.571430;0.714290;,
  0.714290;0.714290;,
  0.857140;0.714290;,
  1.000000;0.714290;,
  0.142860;0.857140;,
  0.000000;0.857140;,
  0.285710;0.857140;,
  0.428570;0.857140;,
  0.571430;0.857140;,
  0.714290;0.857140;,
  0.857140;0.857140;,
  1.000000;0.857140;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
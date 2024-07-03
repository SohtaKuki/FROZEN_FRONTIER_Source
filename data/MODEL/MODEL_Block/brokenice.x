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
 413;
 -14.99595;5.25298;-14.99955;,
 -14.99595;14.99393;-14.99955;,
 -5.32402;14.99393;-14.99955;,
 -7.82471;14.99393;15.00045;,
 -14.99595;14.99393;15.00045;,
 -14.99595;7.41769;15.00045;,
 -14.99595;-15.00607;-14.16501;,
 -14.99595;-15.00607;-14.99955;,
 -14.92380;-15.00607;-14.99955;,
 -3.42858;-2.22380;-14.99955;,
 -3.77671;-2.53041;-14.99955;,
 -4.07319;-2.42665;-14.99955;,
 -14.99595;-5.66754;-14.99955;,
 -14.92380;-15.00607;-14.99955;,
 -14.99595;-15.00607;-14.99955;,
 -14.99595;-5.66597;-14.55904;,
 -14.99595;-5.66754;-14.99955;,
 -14.99595;-15.00607;-14.99955;,
 -14.99595;-15.00607;-14.16501;,
 -3.36555;14.99393;15.00045;,
 -5.84966;12.39845;15.00045;,
 -6.40367;14.04724;-14.99955;,
 -3.12520;14.99393;-14.99955;,
 -14.99595;2.27152;-14.99955;,
 -15.02026;5.41335;-14.99955;,
 -10.38275;11.19835;15.00045;,
 -6.83596;-3.13905;15.00045;,
 0.10549;4.57260;15.00045;,
 -14.99595;7.26872;15.00045;,
 -14.99595;-5.56020;15.00045;,
 -14.99595;2.59166;-14.90741;,
 -14.99595;5.25298;-14.99955;,
 -14.99595;2.27152;-14.99955;,
 15.00405;4.23782;-7.30663;,
 15.00405;3.23377;-14.99955;,
 15.00405;4.96049;-14.99955;,
 -3.51765;-1.16470;-14.99955;,
 -4.87917;-1.90439;-14.99955;,
 -2.27673;-0.95573;-14.99955;,
 -14.99595;-5.20156;-14.99955;,
 -14.99595;-5.20156;-14.99955;,
 -14.99595;-4.94175;-14.58960;,
 -11.29392;-4.56911;-14.99955;,
 -8.35171;-7.70477;-14.99955;,
 -14.29200;-3.00292;15.00045;,
 -12.56834;-4.83990;15.00045;,
 -8.17604;-9.52100;15.00045;,
 -9.91192;-7.67098;15.00045;,
 -11.30135;-8.09990;15.00045;,
 -14.99595;-12.20444;15.00045;,
 -14.99595;-15.00607;15.00045;,
 -10.42401;-4.63815;15.00045;,
 8.46826;-10.69641;-14.99955;,
 15.00405;-15.00607;-14.99955;,
 8.93364;-15.00607;-14.99955;,
 9.15124;14.13693;15.00045;,
 15.00405;14.99393;15.00045;,
 9.48599;14.99393;15.00045;,
 9.10447;14.57008;15.00045;,
 9.05869;14.99393;15.00045;,
 7.10375;1.91374;-14.99955;,
 15.00405;4.96049;-14.99955;,
 15.00405;3.23377;-14.99955;,
 7.21365;1.55502;-14.99955;,
 10.81518;-1.27247;15.00045;,
 11.85071;-10.86216;15.00045;,
 15.00405;-15.00607;15.00045;,
 15.00405;0.02064;15.00045;,
 15.00405;3.34110;15.00045;,
 10.46251;1.78069;15.00045;,
 11.96705;-15.00607;12.04793;,
 15.00405;-15.00607;15.00045;,
 12.29818;-15.00607;15.00045;,
 12.29818;-15.00607;15.00045;,
 6.34479;-2.65249;15.00045;,
 3.50048;-1.16250;15.00045;,
 6.32077;-3.59510;15.00045;,
 6.03003;-15.00607;15.00045;,
 5.25059;-15.00607;5.51831;,
 6.07253;-13.33821;15.00045;,
 6.03003;-15.00607;15.00045;,
 10.43985;2.20339;15.00045;,
 15.00405;4.28577;15.00045;,
 7.27125;2.21682;-14.99955;,
 6.34794;2.13099;-14.99955;,
 5.82726;8.65947;-14.99955;,
 12.07998;14.99393;-14.99955;,
 15.00405;14.99393;-14.99955;,
 15.00405;5.74485;-14.99955;,
 8.31714;1.37123;15.00045;,
 5.84120;7.62231;15.00045;,
 5.56152;1.52084;-14.99955;,
 3.47334;1.05260;-15.00226;,
 3.97164;6.21106;-15.00226;,
 4.10701;-0.68592;15.00045;,
 6.42180;0.37019;15.00045;,
 3.22357;-0.15429;15.00045;,
 5.06977;0.17258;15.00045;,
 3.39950;0.80388;15.00045;,
 3.24528;-0.33512;15.00045;,
 3.23277;-0.23095;15.00045;,
 3.66560;-3.83587;15.00045;,
 3.62435;-1.28167;15.00045;,
 1.40481;14.99393;15.00045;,
 1.58677;14.56016;15.00045;,
 2.35587;7.07267;15.00045;,
 5.00674;-15.00607;15.00045;,
 4.48624;-15.00607;4.77522;,
 4.76441;-12.98776;15.00045;,
 5.00674;-15.00607;15.00045;,
 -4.16643;-6.29617;15.00045;,
 -3.36161;-3.43825;15.00045;,
 -3.87373;-5.80697;15.00045;,
 -9.37767;-15.00607;15.00045;,
 -6.90583;-10.87473;15.00045;,
 4.19336;9.69067;-14.99955;,
 4.32847;14.99393;-14.99955;,
 7.36636;14.99393;-14.99955;,
 4.10267;6.13150;-14.99955;,
 8.24326;14.44501;15.00045;,
 8.57168;14.99393;15.00045;,
 1.35446;2.93128;15.00045;,
 -1.29358;-1.49457;15.00045;,
 -2.16914;-2.41257;15.00045;,
 -5.25755;-8.11984;15.00045;,
 1.05465;4.60585;-14.96636;,
 1.31370;3.03307;-14.99955;,
 -1.97783;-0.62366;-14.99955;,
 1.88155;15.03038;-14.96636;,
 -10.36871;-15.00607;-9.66650;,
 -10.58299;-15.00607;-14.99955;,
 2.86827;5.22839;15.00045;,
 5.41163;7.49055;15.00045;,
 -1.10000;0.41054;-14.99955;,
 -0.92403;0.70466;-14.99955;,
 2.42074;4.33464;-15.00226;,
 2.29556;1.66349;-15.00226;,
 -2.78700;-1.97609;-14.99955;,
 1.24815;-0.24106;-14.99955;,
 -6.38324;-10.00129;15.00045;,
 4.03032;8.94173;15.00045;,
 6.59635;11.91658;15.00045;,
 6.77498;14.23179;15.00045;,
 3.78863;14.27528;15.00045;,
 2.57315;15.03038;-14.96636;,
 3.00443;6.63979;-14.96636;,
 2.46400;4.31101;-14.99955;,
 5.19026;7.53753;15.00045;,
 4.12258;7.30112;15.00045;,
 6.59571;11.89131;15.00045;,
 15.00405;-1.74611;-9.69876;,
 15.00405;-15.00607;-14.99955;,
 15.00405;-2.31389;-14.99955;,
 -14.92098;-6.89150;15.00045;,
 -14.99595;-6.86647;15.00045;,
 -14.99595;-6.91102;15.00045;,
 -14.99595;-6.91102;15.00045;,
 -14.99595;-6.86647;15.00045;,
 -14.99595;-6.93877;14.74139;,
 -14.85539;-6.87442;15.00045;,
 -11.48313;-5.99646;15.00045;,
 7.80187;-4.18899;-14.99955;,
 15.00405;-2.31389;-14.99955;,
 3.68635;-5.26046;-14.99955;,
 3.75313;0.06336;-14.99955;,
 5.84037;-4.69966;-14.99955;,
 3.56411;-15.00607;-14.99955;,
 3.48658;0.39400;-14.99955;,
 -5.36686;-3.19808;15.00045;,
 6.52443;10.98948;15.00045;,
 6.91015;12.10167;15.00045;,
 6.92743;12.15148;15.00045;,
 6.85458;11.96456;15.00045;,
 7.00522;12.37579;15.00045;,
 7.49246;3.45333;15.00045;,
 5.45336;3.82581;15.00045;,
 5.66731;0.79789;15.00045;,
 -4.13236;-2.92845;-14.99955;,
 -2.94783;-2.24489;-14.99955;,
 -3.22787;-2.71294;-14.99955;,
 -6.80779;-6.71273;15.00045;,
 -6.65119;-8.29460;15.00045;,
 -6.88026;-5.98067;15.00045;,
 -2.52467;-3.55218;15.00045;,
 -6.60448;-8.76650;15.00045;,
 -1.63601;-15.00607;-14.99955;,
 -4.15953;-4.27009;-14.99955;,
 2.02862;-0.62562;-14.99955;,
 3.75519;-15.00607;-14.99955;,
 -6.48493;-9.97405;15.00045;,
 -6.46818;-10.14325;15.00045;,
 -6.33561;-11.48244;15.00045;,
 -3.02936;-15.00607;15.00045;,
 -6.94102;-5.36692;15.00045;,
 -6.88026;-5.98066;15.00045;,
 -2.90130;-3.76217;15.00045;,
 -4.67900;-4.22500;15.00045;,
 -5.33913;-6.24164;-14.99955;,
 -10.58299;-15.00607;-14.99955;,
 -5.70413;-4.68756;-14.99955;,
 -5.89746;-15.00607;15.00045;,
 -5.98678;-15.00607;15.00045;,
 -5.04217;-15.00607;5.19512;,
 -7.77514;-7.01135;15.00045;,
 -7.34306;-8.85105;15.00045;,
 -6.06654;-14.34864;15.00045;,
 -5.89746;-15.00607;15.00045;,
 -6.85506;-10.92883;15.00045;,
 -5.98678;-15.00607;15.00045;,
 -7.88557;-6.54118;15.00045;,
 -7.28607;-9.09373;15.00045;,
 -4.26359;-15.00607;-3.73120;,
 -1.81997;-15.00607;-14.99955;,
 -1.63601;-15.00607;-14.99955;,
 -4.18921;-15.00607;-3.65890;,
 -1.81997;-15.00607;-14.99955;,
 -5.33913;-6.24164;-14.99955;,
 -7.11922;-9.80412;15.00045;,
 -6.87850;-10.82904;15.00045;,
 -8.03201;-5.91768;15.00045;,
 -7.88557;-6.54118;15.00045;,
 -14.99595;-13.54066;1.09019;,
 -14.99595;-15.00607;1.59310;,
 15.00405;14.99393;-9.81920;,
 15.00405;14.99393;-14.99955;,
 12.07998;14.99393;-14.99955;,
 11.62117;14.99393;-9.69325;,
 -5.82045;14.99393;-9.04395;,
 -3.17212;14.99393;-11.69830;,
 -3.12520;14.99393;-14.99955;,
 -5.32402;14.99393;-14.99955;,
 15.00405;3.99951;-6.04610;,
 15.00405;-15.00607;0.47629;,
 -14.99595;-10.99264;0.21576;,
 -14.99595;-6.05476;-1.47884;,
 -14.99595;-5.64866;-9.72347;,
 -14.99595;-5.61970;-1.62815;,
 -14.99595;-0.34074;-0.53989;,
 -14.99595;4.14429;-2.04671;,
 15.00405;-15.00607;0.47629;,
 10.68731;-15.00607;0.63698;,
 8.93364;-15.00607;-14.99955;,
 15.00405;-15.00607;-14.99955;,
 4.86718;-15.00607;0.85366;,
 3.56411;-15.00607;-14.99955;,
 15.00405;14.99393;-9.81920;,
 15.00405;5.33161;-6.50325;,
 15.00405;5.74485;-14.99955;,
 15.00405;14.99393;-14.99955;,
 1.63015;14.99393;-9.26695;,
 1.88155;15.03038;-14.96636;,
 4.34196;-15.00607;0.87321;,
 3.75519;-15.00607;-14.99955;,
 -0.86152;-15.00607;1.12130;,
 -0.71757;-15.00607;-1.70390;,
 2.07599;-15.00607;1.01195;,
 -14.99595;-15.00607;1.59310;,
 -10.36869;-15.00607;-9.66647;,
 -9.92391;-15.00607;1.40428;,
 7.36636;14.99393;-14.99955;,
 7.58559;14.99393;-9.54303;,
 4.32847;14.99393;-14.99955;,
 2.37772;14.99393;-9.43879;,
 -14.99595;-10.99264;0.21576;,
 2.07599;-15.00607;1.01195;,
 -4.65809;-15.00607;1.20825;,
 -4.18921;-15.00607;-3.65890;,
 -2.81136;-15.00607;1.13953;,
 -4.69454;-15.00607;1.20961;,
 -4.26359;-15.00607;-3.73120;,
 -5.62195;-15.00607;1.24416;,
 -14.99595;5.98739;-1.40312;,
 -14.99595;14.99393;-3.60448;,
 -14.99595;14.99393;-14.99955;,
 -6.24251;14.99393;-3.98067;,
 -14.99595;14.99393;-14.99955;,
 -14.99595;14.99393;-3.60448;,
 11.19201;14.99393;-4.23716;,
 15.00405;14.99393;-4.89379;,
 -6.24251;14.99393;-3.98068;,
 -3.21244;14.99393;-5.07127;,
 -14.99595;4.12965;-2.14034;,
 -14.99595;4.33590;-2.13038;,
 -14.99595;5.98739;-1.40311;,
 -14.99595;5.93177;-2.17396;,
 15.00405;4.06097;-6.37120;,
 15.00405;4.19946;-6.35248;,
 15.00405;4.18977;-6.11139;,
 15.00405;14.99393;-4.89379;,
 15.00405;5.31693;-6.20147;,
 1.88467;14.99393;-4.26718;,
 7.78485;14.99393;-4.19621;,
 2.78596;14.99393;-4.26674;,
 15.00405;5.07000;-1.12442;,
 15.00405;5.19213;-3.63556;,
 15.00405;6.39995;-1.33914;,
 15.00405;3.98224;-0.94880;,
 15.00405;3.00607;-0.79120;,
 10.86259;-15.00607;2.19987;,
 4.98751;-15.00607;2.31762;,
 4.39580;-15.00607;2.32947;,
 2.01951;-15.00607;2.37711;,
 -0.15986;-15.00607;2.45006;,
 -0.93000;-15.00607;2.46549;,
 -9.87525;-15.00607;2.61549;,
 -14.99595;-15.00607;2.71812;,
 -14.99595;-10.49742;1.99019;,
 -14.99595;-10.50254;1.99102;,
 2.01951;-15.00607;2.37711;,
 -3.10979;-15.00607;2.47992;,
 -4.78383;-15.00607;2.51346;,
 -4.80831;-15.00607;2.51394;,
 -5.65608;-15.00607;2.53093;,
 -5.97500;-15.00607;2.53731;,
 -14.99595;6.28342;-0.71908;,
 -14.99595;6.25290;-0.71415;,
 15.00405;8.09767;1.88869;,
 15.00405;14.99393;15.00045;,
 15.00405;4.28577;15.00045;,
 15.00405;4.92223;1.91386;,
 -14.99595;-15.00607;6.37888;,
 -14.99595;-15.00607;15.00045;,
 -14.99595;-12.20444;15.00045;,
 -14.99595;-13.03413;6.36324;,
 -14.99595;-13.40905;2.46027;,
 -14.99595;-15.00607;2.71812;,
 15.00405;3.86683;1.92224;,
 15.00405;3.34110;15.00045;,
 15.00405;0.02064;15.00045;,
 15.00405;2.49103;1.93315;,
 15.00405;-14.71327;2.06959;,
 15.00405;-15.00607;2.11687;,
 15.00405;-15.00607;2.07191;,
 -14.99595;-9.28528;6.33348;,
 -14.99595;-6.43846;6.31093;,
 -14.99595;-6.19139;1.29498;,
 -14.99595;-10.49742;1.99019;,
 -14.99595;-5.59132;6.30421;,
 -14.99595;-5.56020;15.00045;,
 -14.99595;7.26872;15.00045;,
 -14.99595;3.64992;6.23090;,
 -14.99595;1.12561;0.11365;,
 -14.99595;-5.60958;1.20105;,
 -14.99595;5.89454;6.21313;,
 -14.99595;4.84674;-0.48713;,
 10.91410;-15.00607;2.65909;,
 14.64014;-15.00607;2.12416;,
 15.00405;-15.00607;2.11687;,
 11.96708;-15.00607;12.04796;,
 15.00405;-15.00607;2.07191;,
 5.25059;-15.00607;5.51831;,
 5.08437;-15.00607;3.49604;,
 4.48621;-15.00607;4.77519;,
 4.44233;-15.00607;3.58822;,
 3.41672;-15.00607;3.73546;,
 0.82604;-15.00607;4.31710;,
 -3.02936;-15.00607;15.00045;,
 -1.03798;-15.00607;4.58470;,
 -9.75428;-15.00607;5.62636;,
 -9.37767;-15.00607;15.00045;,
 -14.99595;-15.00607;6.37888;,
 -14.99595;-9.30366;6.33367;,
 -14.99595;-9.28527;6.33351;,
 3.41672;-15.00607;3.73546;,
 -3.61407;-15.00607;4.74484;,
 -5.01822;-15.00607;4.94642;,
 -5.02051;-15.00607;4.94676;,
 -5.72282;-15.00607;5.04758;,
 -6.69860;-15.00607;5.18767;,
 -14.99595;6.78311;6.20607;,
 -14.99595;7.41769;15.00045;,
 -14.99595;14.99393;15.00045;,
 -14.99595;14.99393;6.14095;,
 -14.99595;14.99393;-3.09655;,
 -14.99595;6.28342;-0.71908;,
 -14.99595;14.99393;6.14095;,
 -7.82471;14.99393;15.00045;,
 -6.99041;14.99393;4.99163;,
 -6.24981;14.99393;-3.37721;,
 -14.99595;14.99393;-3.09655;,
 10.56940;14.99393;2.47065;,
 9.48599;14.99393;15.00045;,
 15.00405;14.99393;1.83398;,
 15.00405;14.99393;-4.03901;,
 11.01187;14.99393;-4.05619;,
 -6.99041;14.99393;4.99163;,
 -3.36555;14.99393;15.00045;,
 -3.28110;14.99393;4.45910;,
 -3.22645;14.99393;-4.08255;,
 -6.38277;14.99393;-3.55102;,
 -14.99595;6.70028;6.20673;,
 -14.99595;6.78311;6.20607;,
 15.00405;14.99393;1.83398;,
 15.00405;14.99393;-4.03901;,
 2.59516;14.99393;15.00045;,
 2.29879;14.99393;3.86773;,
 1.97787;14.99393;-3.72961;,
 8.08261;14.99393;2.82766;,
 8.57168;14.99393;15.00045;,
 7.86520;14.99393;-3.70264;,
 5.82052;14.99393;3.15242;,
 6.79439;14.99393;15.00045;,
 5.35317;14.99393;-3.43501;,
 3.31382;14.99393;3.51230;,
 3.72717;14.99393;15.00045;,
 3.09792;14.99393;-3.55193;,
 -14.99595;5.79619;-4.73572;,
 -14.99595;4.36679;-4.85501;,
 -14.99595;3.79690;-4.90257;,
 15.00405;5.29128;-5.67411;,
 15.00405;9.09895;-5.43883;,
 -14.99595;4.92392;-2.14644;,
 -14.99595;5.90380;-2.70251;;
 
 283;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;12,13,14;,
 4;15,16,17,18;,
 3;19,3,20;,
 3;21,2,22;,
 3;23,0,24;,
 3;20,3,25;,
 3;20,26,27;,
 3;28,29,25;,
 3;30,31,32;,
 3;33,34,35;,
 4;36,9,11,37;,
 4;36,37,24,21;,
 3;38,9,36;,
 4;38,36,21,22;,
 4;37,39,23,24;,
 4;40,41,30,32;,
 4;42,11,10,43;,
 4;42,43,13,12;,
 3;44,29,45;,
 4;44,45,26,20;,
 3;44,20,25;,
 4;46,47,48,49;,
 3;46,49,50;,
 3;51,48,47;,
 3;52,53,54;,
 3;55,56,57;,
 3;55,57,58;,
 3;58,57,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;64,67,68,69;,
 3;70,71,72;,
 3;73,66,65;,
 3;74,75,76;,
 4;74,76,65,64;,
 4;77,78,70,72;,
 4;76,79,73,65;,
 3;80,73,79;,
 4;81,82,56,55;,
 3;83,60,84;,
 4;83,84,85,86;,
 3;83,86,87;,
 3;83,87,88;,
 4;89,81,55,90;,
 3;84,60,91;,
 4;84,91,92,93;,
 3;84,93,85;,
 4;94,75,74,95;,
 4;89,95,74,64;,
 3;89,64,69;,
 3;96,97,98;,
 3;99,97,100;,
 3;100,97,96;,
 3;101,75,102;,
 4;103,19,20,104;,
 4;104,20,27,105;,
 4;106,107,78,77;,
 4;101,108,79,76;,
 3;101,76,75;,
 4;108,109,80,79;,
 3;110,111,112;,
 4;113,114,46,50;,
 3;115,116,117;,
 4;115,117,86,118;,
 4;119,58,59,120;,
 4;121,27,26,122;,
 4;121,122,96,98;,
 4;122,123,100,96;,
 4;110,124,101,102;,
 3;110,102,111;,
 3;125,126,127;,
 4;125,127,38,22;,
 3;125,22,128;,
 4;129,6,8,130;,
 3;121,98,131;,
 4;121,131,105,27;,
 3;132,105,131;,
 4;132,131,98,97;,
 3;133,38,134;,
 4;133,134,135,136;,
 4;137,9,38,133;,
 4;137,133,136,138;,
 4;124,139,108,101;,
 3;139,109,108;,
 4;140,141,142,143;,
 4;140,143,104,105;,
 4;144,145,125,128;,
 4;145,146,126,125;,
 3;147,132,148;,
 4;147,149,141,140;,
 4;147,140,105,132;,
 3;150,151,152;,
 4;150,152,34,33;,
 3;153,154,155;,
 4;153,155,49,48;,
 3;156,157,158;,
 3;159,51,160;,
 3;159,29,154;,
 3;159,154,153;,
 4;159,153,48,51;,
 4;161,63,62,162;,
 4;161,162,53,52;,
 3;163,164,165;,
 4;163,165,52,54;,
 3;163,54,166;,
 3;161,52,165;,
 4;161,165,164,167;,
 3;161,167,63;,
 3;168,122,26;,
 4;169,90,55,170;,
 3;171,172,170;,
 4;171,170,55,58;,
 3;173,172,171;,
 4;173,171,58,119;,
 3;174,90,175;,
 4;174,175,176,89;,
 4;177,10,178,179;,
 4;180,181,110,112;,
 4;182,180,112,183;,
 4;181,184,124,110;,
 4;185,186,178,187;,
 3;185,187,188;,
 4;184,189,139,124;,
 3;190,139,189;,
 4;190,191,192,109;,
 3;190,109,139;,
 4;193,194,195,196;,
 4;197,198,13,199;,
 4;197,199,177,179;,
 3;200,201,202;,
 4;203,47,46,204;,
 4;205,206,192,191;,
 4;205,207,114,113;,
 3;205,113,208;,
 3;209,47,203;,
 3;204,46,210;,
 4;211,129,130,212;,
 4;211,212,213,214;,
 3;215,198,216;,
 4;215,216,186,185;,
 3;210,46,217;,
 4;217,46,114,218;,
 3;218,114,207;,
 4;219,51,47,220;,
 3;221,18,222;,
 4;223,224,225,226;,
 4;227,228,229,230;,
 4;231,232,151,33;,
 4;233,234,235,15;,
 3;233,15,18;,
 4;236,237,41,235;,
 4;237,238,30,41;,
 4;239,240,241,242;,
 4;243,244,241,240;,
 4;245,246,247,248;,
 4;228,249,250,229;,
 4;251,252,244,243;,
 3;253,254,255;,
 4;256,6,257,258;,
 4;226,225,259,260;,
 4;260,259,261,262;,
 3;263,18,221;,
 4;251,264,214,213;,
 3;251,213,252;,
 4;265,266,254,267;,
 3;267,254,253;,
 4;265,268,269,266;,
 3;270,269,268;,
 4;270,258,257,269;,
 4;271,272,273,31;,
 4;274,230,275,276;,
 4;277,278,223,226;,
 4;279,280,228,227;,
 3;281,238,282;,
 3;283,284,282;,
 3;285,33,286;,
 4;285,286,287,231;,
 4;288,289,246,245;,
 4;280,290,249,228;,
 4;291,277,226,260;,
 4;292,291,260,262;,
 3;293,294,295;,
 4;296,297,231,287;,
 4;298,299,243,240;,
 4;299,300,251,243;,
 4;301,302,253,255;,
 3;303,253,302;,
 4;304,305,256,258;,
 3;306,263,307;,
 4;300,308,264,251;,
 4;309,310,265,267;,
 4;303,309,267,253;,
 4;310,311,268,265;,
 4;311,312,270,268;,
 3;313,270,312;,
 4;313,304,258,270;,
 3;314,283,315;,
 4;316,317,318,319;,
 4;316,319,293,295;,
 4;320,321,322,323;,
 4;320,323,324,325;,
 4;326,327,328,329;,
 4;326,329,297,296;,
 3;330,297,329;,
 4;330,329,328,71;,
 3;330,71,331;,
 3;330,331,332;,
 4;330,332,232,231;,
 3;330,231,297;,
 3;333,157,334;,
 4;333,334,335,336;,
 4;337,338,339,340;,
 4;337,340,341,342;,
 3;340,339,343;,
 4;340,343,344,341;,
 3;345,298,346;,
 4;345,346,347,71;,
 3;345,71,348;,
 3;349,347,346;,
 4;349,346,298,240;,
 3;349,240,239;,
 4;345,348,350,351;,
 4;345,351,299,298;,
 4;351,350,352,353;,
 4;351,353,300,299;,
 4;354,107,106,355;,
 4;354,355,302,301;,
 4;355,106,356,357;,
 4;355,357,303,302;,
 4;358,359,321,360;,
 4;358,360,305,304;,
 4;323,322,156,361;,
 4;323,361,307,324;,
 4;361,156,158,362;,
 4;361,362,306,307;,
 3;353,352,363;,
 4;353,363,308,300;,
 4;364,200,202,365;,
 4;364,365,310,309;,
 4;357,356,200,364;,
 4;357,364,309,303;,
 3;365,202,366;,
 4;365,366,311,310;,
 4;366,202,201,367;,
 4;366,367,312,311;,
 4;367,201,359,368;,
 4;367,368,313,312;,
 3;368,359,358;,
 4;368,358,304,313;,
 4;369,370,371,372;,
 4;369,372,373,374;,
 4;375,371,376,377;,
 4;375,377,378,379;,
 4;380,381,317,382;,
 4;380,382,383,384;,
 4;385,376,386,387;,
 4;385,387,388,389;,
 3;343,339,390;,
 4;343,390,315,344;,
 4;390,339,370,391;,
 4;390,391,314,315;,
 3;392,317,316;,
 4;392,316,295,393;,
 4;387,386,394,395;,
 4;387,395,396,388;,
 4;397,398,381,380;,
 4;397,380,384,399;,
 4;400,401,398,397;,
 4;400,397,399,402;,
 4;403,404,401,400;,
 4;403,400,402,405;,
 3;406,31,407;,
 4;406,407,281,282;,
 3;408,281,407;,
 4;408,407,31,30;,
 4;409,410,393,295;,
 3;409,295,294;,
 3;411,284,412;,
 4;411,412,406,282;;
 
 MeshMaterialList {
  4;
  283;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.446667;0.836667;0.850000;1.000000;;
   70.000000;
   0.690000;0.690000;0.690000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.254400;0.762400;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.318000;0.953000;1.000000;;
  }
  Material {
   0.896400;0.900000;0.490500;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  69;
  0.000000;0.000000;-1.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.002873;-0.000042;-0.999996;,
  0.000000;0.000000;1.000000;,
  0.000063;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000971;0.000071;-0.999999;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000660;0.000053;-1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000001;0.000001;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000001;0.000000;-1.000000;,
  0.000839;-0.000292;-1.000000;,
  0.001079;-0.000094;-0.999999;,
  0.000432;-0.000037;-1.000000;,
  0.000420;-0.000146;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000171;-0.000616;-1.000000;,
  0.003317;-0.000263;-0.999995;,
  -0.019763;0.018076;-0.999641;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000554;-0.000145;-1.000000;,
  -0.000937;0.000326;-1.000000;,
  -0.000085;-0.000308;-1.000000;,
  -0.007479;0.009097;-0.999931;,
  -0.005607;0.007197;-0.999958;,
  -0.000277;-0.000073;-1.000000;,
  -0.000469;0.000163;-1.000000;,
  -0.019712;0.018317;-0.999638;,
  -0.009857;0.009159;-0.999910;,
  0.000000;0.000000;-1.000000;,
  0.000001;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.001306;0.999999;0.000769;,
  0.000000;-1.000000;0.000000;,
  -0.002612;0.999995;0.001538;,
  -0.000001;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;-0.000003;0.000000;,
  -1.000000;-0.000005;0.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.005223;0.999982;0.003076;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;-0.000005;0.000000;,
  -1.000000;0.000000;-0.000000;;
  283;
  3;0,0,0;,
  3;5,4,4;,
  3;1,1,1;,
  3;0,0,0;,
  3;0,0,0;,
  4;7,7,7,7;,
  3;3,5,3;,
  3;11,0,8;,
  3;10,10,10;,
  3;3,5,3;,
  3;3,3,3;,
  3;9,3,3;,
  3;7,7,7;,
  3;6,6,6;,
  4;15,0,0,14;,
  4;15,14,62,11;,
  3;12,0,15;,
  4;12,15,11,8;,
  4;14,13,13,62;,
  4;7,7,7,7;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;20,2,17;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;0,0,63,19;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;1,1,1;,
  3;3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;0,0,26;,
  4;0,26,18,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;3,3,3,3;,
  3;26,0,27;,
  4;26,27,24,25;,
  3;26,25,18;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;33,32,1,1;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;0,0,0;,
  4;3,3,3,3;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  3;38,31,37;,
  4;38,37,12,8;,
  3;38,8,30;,
  4;1,1,1,1;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;39,12,40;,
  4;39,40,35,34;,
  4;36,0,12,39;,
  4;36,39,34,29;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,42,38,30;,
  4;42,41,31,38;,
  3;28,28,28;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;6,6,6;,
  4;6,6,6,6;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;7,7,7;,
  3;0,0,0;,
  3;3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  4;43,19,63,64;,
  4;43,64,2,20;,
  3;45,21,44;,
  4;45,44,20,17;,
  3;45,17,0;,
  3;43,20,44;,
  4;43,44,21,23;,
  3;43,23,19;,
  3;9,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  3;0,0,28;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;46,1,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;3,3,9;,
  3;3,3,3;,
  3;3,3,3;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;0,0,0;,
  4;0,0,0,0;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;7,7,7;,
  4;22,22,22,22;,
  4;22,47,49,22;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  3;7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;47,49,65,49;,
  4;1,1,1,1;,
  3;48,16,50;,
  4;1,1,1,1;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  3;7,7,7;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,16,51;,
  3;51,16,48;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;7,7,7,7;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,47,22;,
  3;7,7,7;,
  3;7,7,7;,
  3;6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;22,22,49,47;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  3;6,6,6;,
  4;6,6,6,6;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;53,54,48,50;,
  3;52,48,54;,
  4;1,1,1,1;,
  3;7,7,7;,
  4;1,1,1,1;,
  4;52,1,1,51;,
  4;52,52,51,48;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;7,7,7;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;7,7,7;,
  4;7,7,7,7;,
  4;7,7,60,7;,
  4;7,7,7,7;,
  3;7,60,7;,
  4;7,7,7,7;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;57,32,33,58;,
  4;57,58,54,53;,
  4;58,33,66,56;,
  4;58,56,52,54;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;59,46,1,1;,
  4;59,1,1,52;,
  4;56,66,46,59;,
  4;56,59,52,52;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;55,67,68,55;,
  4;55,55,7,7;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  3;7,60,60;,
  4;7,60,7,7;,
  4;60,60,67,61;,
  4;60,61,7,7;,
  3;6,6,6;,
  4;6,6,6,6;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  3;7,7,7;,
  4;7,7,7,7;,
  3;7,7,7;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  3;6,6,6;,
  3;7,7,7;,
  4;7,7,7,7;;
 }
 MeshTextureCoords {
  413;
  0.000000;0.340605;,
  0.000000;0.000000;,
  0.322398;0.000000;,
  0.760959;0.000000;,
  1.000000;0.000000;,
  1.000000;0.252541;,
  0.000000;0.027818;,
  0.000000;0.000000;,
  0.002405;0.000000;,
  0.385579;0.574310;,
  0.373975;0.587202;,
  0.364092;0.580686;,
  0.000000;0.688715;,
  0.002405;1.000000;,
  0.000000;1.000000;,
  0.985316;0.688663;,
  1.000000;0.688715;,
  1.000000;1.000000;,
  0.972182;1.000000;,
  0.612320;0.000000;,
  0.695124;0.086516;,
  0.329954;0.068685;,
  0.395692;0.000000;,
  0.000000;0.413434;,
  0.042734;0.368784;,
  0.846227;0.244395;,
  0.728000;0.604432;,
  0.496619;0.347378;,
  1.000000;0.405063;,
  1.000000;0.685138;,
  0.996929;0.413409;,
  1.000000;0.340605;,
  1.000000;0.413434;,
  0.256431;0.391088;,
  0.000000;0.392005;,
  0.000000;0.353835;,
  0.382610;0.547320;,
  0.337226;0.562970;,
  0.423974;0.531655;,
  0.000000;0.662537;,
  1.000000;0.662537;,
  0.986335;0.664523;,
  0.123401;0.652101;,
  0.221475;0.756623;,
  0.976535;0.617882;,
  0.919080;0.661128;,
  0.772670;0.817164;,
  0.830533;0.755497;,
  0.876847;0.769794;,
  1.000000;0.906612;,
  1.000000;1.000000;,
  0.847602;0.737305;,
  0.782140;0.856344;,
  1.000000;1.000000;,
  0.797653;1.000000;,
  0.195094;0.028567;,
  0.000000;0.000000;,
  0.183936;0.000000;,
  0.196653;0.014128;,
  0.198179;0.000000;,
  0.736656;0.435129;,
  1.000000;0.353835;,
  1.000000;0.392005;,
  0.740320;0.469055;,
  0.139629;0.542213;,
  0.105112;0.861870;,
  0.000000;1.000000;,
  0.000000;0.499110;,
  0.000000;0.388427;,
  0.151385;0.433345;,
  0.898767;0.901583;,
  1.000000;1.000000;,
  0.909804;1.000000;,
  0.090196;1.000000;,
  0.288642;0.588214;,
  0.308652;0.594391;,
  0.289443;0.619634;,
  0.700866;1.000000;,
  0.674885;0.683929;,
  0.297718;0.944405;,
  0.299134;1.000000;,
  0.152140;0.426351;,
  0.000000;0.356938;,
  0.742240;0.425903;,
  0.735969;0.428764;,
  0.712471;0.211149;,
  0.902531;0.000000;,
  1.000000;0.000000;,
  1.000000;0.308302;,
  0.197384;0.446993;,
  0.279916;0.245720;,
  0.691392;0.449103;,
  0.632240;0.467363;,
  0.636621;0.295414;,
  0.363235;0.522662;,
  0.286075;0.487458;,
  0.392683;0.504941;,
  0.379660;0.501077;,
  0.395673;0.480033;,
  0.391959;0.510968;,
  0.392376;0.507496;,
  0.377948;0.627660;,
  0.379324;0.616207;,
  0.453308;0.000000;,
  0.447243;0.050519;,
  0.421606;0.264042;,
  0.666756;1.000000;,
  0.649406;0.659159;,
  0.341321;0.932723;,
  0.333244;1.000000;,
  0.639016;0.709670;,
  0.612189;0.688093;,
  0.629260;0.693363;,
  0.812724;1.000000;,
  0.730329;0.862288;,
  0.639643;0.176775;,
  0.644147;0.000000;,
  0.745410;0.000000;,
  0.636621;0.295414;,
  0.225360;0.018297;,
  0.214412;0.000000;,
  0.454986;0.402088;,
  0.543254;0.549617;,
  0.572440;0.598396;,
  0.675387;0.770459;,
  0.537506;0.347484;,
  0.543655;0.398695;,
  0.433937;0.520586;,
  0.495786;0.000000;,
  0.154241;0.177768;,
  0.147099;0.000000;,
  0.413381;0.332550;,
  0.368265;0.257144;,
  0.428072;0.530390;,
  0.433937;0.520586;,
  0.543655;0.398695;,
  0.554771;0.491278;,
  0.406965;0.567965;,
  0.556758;0.523520;,
  0.712910;0.833174;,
  0.365527;0.201740;,
  0.276269;0.102578;,
  0.274302;0.025405;,
  0.373847;0.039860;,
  0.563695;0.000000;,
  0.578071;0.279686;,
  0.581998;0.356097;,
  0.363121;0.248547;,
  0.362716;0.256427;,
  0.276290;0.103421;,
  0.176693;0.580430;,
  0.000000;1.000000;,
  0.000000;0.576927;,
  0.997501;0.807040;,
  1.000000;0.807812;,
  1.000000;0.808636;,
  0.000000;0.808636;,
  0.000000;0.807812;,
  0.008635;0.809519;,
  0.995315;0.805644;,
  0.882906;0.699679;,
  0.759927;0.650633;,
  1.000000;0.576927;,
  0.622743;0.840072;,
  0.624969;0.752707;,
  0.694544;0.798584;,
  0.618669;1.000000;,
  0.631373;0.501381;,
  0.792563;0.676158;,
  0.277056;0.133482;,
  0.269797;0.096409;,
  0.269221;0.094748;,
  0.274829;0.100979;,
  0.266628;0.087271;,
  0.224874;0.379954;,
  0.283814;0.398730;,
  0.285712;0.473201;,
  0.362120;0.600373;,
  0.401604;0.605421;,
  0.392269;0.619893;,
  0.727062;0.723555;,
  0.721842;0.776284;,
  0.729477;0.699153;,
  0.584291;0.618204;,
  0.720284;0.792014;,
  0.391844;1.000000;,
  0.361214;0.668041;,
  0.558297;0.708744;,
  0.615850;1.000000;,
  0.716299;0.832266;,
  0.715741;0.837906;,
  0.711322;0.882545;,
  0.601114;1.000000;,
  0.731502;0.678695;,
  0.729477;0.699153;,
  0.596845;0.625203;,
  0.656102;0.640631;,
  0.321894;0.729002;,
  0.147099;1.000000;,
  0.309727;0.658578;,
  0.303283;1.000000;,
  0.300305;1.000000;,
  0.331792;0.673156;,
  0.759307;0.733509;,
  0.744904;0.794833;,
  0.701864;0.978086;,
  0.696717;1.000000;,
  0.728637;0.864092;,
  0.699695;1.000000;,
  0.762987;0.717837;,
  0.743004;0.802922;,
  0.357745;0.375612;,
  0.385830;0.000000;,
  0.391844;0.000000;,
  0.360224;0.378022;,
  0.385830;1.000000;,
  0.321894;0.729002;,
  0.737442;0.826602;,
  0.729418;0.860766;,
  0.767869;0.697053;,
  0.762987;0.717837;,
  0.463675;0.951153;,
  0.446912;1.000000;,
  1.000000;0.827322;,
  1.000000;1.000000;,
  0.902531;1.000000;,
  0.887237;0.823123;,
  0.305850;0.801480;,
  0.394127;0.804767;,
  0.395692;1.000000;,
  0.322398;1.000000;,
  0.298448;0.397192;,
  0.515861;1.000000;,
  0.492823;0.905237;,
  0.549310;0.728011;,
  0.824131;0.688086;,
  0.554287;0.687121;,
  0.614675;0.566756;,
  0.665981;0.410638;,
  1.000000;0.515861;,
  0.856109;0.521218;,
  0.797653;0.000000;,
  1.000000;0.000000;,
  0.662104;0.528440;,
  0.618669;0.000000;,
  0.172678;0.000000;,
  0.283210;0.322077;,
  0.000000;0.308302;,
  0.000000;0.000000;,
  0.505513;0.808913;,
  0.495786;1.000000;,
  0.642784;0.529092;,
  0.615850;0.000000;,
  0.422458;0.537362;,
  0.427256;0.443188;,
  0.520375;0.533717;,
  0.000000;0.553088;,
  0.154242;0.177769;,
  0.169068;0.546794;,
  0.745410;1.000000;,
  0.752718;0.818116;,
  0.644147;1.000000;,
  0.659383;0.814641;,
  0.492823;0.905237;,
  0.520375;0.533717;,
  0.344595;0.540260;,
  0.360224;0.378022;,
  0.406153;0.537969;,
  0.343380;0.540305;,
  0.357745;0.375612;,
  0.312467;0.541457;,
  0.660734;0.310728;,
  0.620164;0.000000;,
  1.000000;0.000000;,
  0.291781;0.632704;,
  0.000000;1.000000;,
  0.000000;0.620164;,
  0.872932;0.657680;,
  1.000000;0.663141;,
  0.291781;0.632704;,
  0.392784;0.637045;,
  0.669102;0.410664;,
  0.668173;0.400171;,
  0.660734;0.310728;,
  0.686429;0.312991;,
  0.287612;0.395618;,
  0.288236;0.390974;,
  0.296272;0.390945;,
  0.336859;0.000000;,
  0.293269;0.322567;,
  0.513997;0.642255;,
  0.759360;0.652799;,
  0.672991;0.649088;,
  0.462504;0.330798;,
  0.378799;0.326727;,
  0.455347;0.286466;,
  0.468358;0.390329;,
  0.473612;0.422639;,
  0.861951;0.573314;,
  0.666115;0.577239;,
  0.645255;0.577634;,
  0.567182;0.579222;,
  0.445846;0.581654;,
  0.420175;0.582168;,
  0.170690;0.587168;,
  0.000000;0.590589;,
  0.433675;0.893544;,
  0.433648;0.893638;,
  0.567182;0.579222;,
  0.396205;0.582649;,
  0.340404;0.583767;,
  0.339588;0.583783;,
  0.311329;0.584349;,
  0.300698;0.584562;,
  0.523984;0.298686;,
  0.523820;0.330276;,
  0.562941;0.229875;,
  1.000000;0.000000;,
  1.000000;0.356938;,
  0.563780;0.335723;,
  0.287386;1.000000;,
  0.000000;1.000000;,
  0.000000;0.906612;,
  0.287907;0.934269;,
  0.418006;0.946766;,
  0.409411;1.000000;,
  0.564059;0.389987;,
  1.000000;0.388427;,
  1.000000;0.499110;,
  0.564423;0.435831;,
  0.568971;0.990614;,
  0.570547;1.000000;,
  0.569049;1.000000;,
  0.288899;0.864923;,
  0.289651;0.765733;,
  0.456849;0.741443;,
  0.433675;0.893544;,
  0.289875;0.686175;,
  0.000000;0.685138;,
  0.000000;0.405063;,
  0.292318;0.481958;,
  0.496227;0.535598;,
  0.459980;0.686783;,
  0.292911;0.407515;,
  0.516253;0.409385;,
  0.863668;0.588621;,
  0.987870;0.570790;,
  1.000000;0.570547;,
  0.898768;0.901584;,
  1.000000;0.569049;,
  0.674885;0.683929;,
  0.669344;0.616520;,
  0.649405;0.659158;,
  0.647391;0.619592;,
  0.613756;0.624500;,
  0.478710;0.643888;,
  0.398886;1.000000;,
  0.416576;0.652808;,
  0.174722;0.687530;,
  0.187276;1.000000;,
  0.000000;0.712614;,
  0.288893;0.865264;,
  0.288898;0.864923;,
  0.613756;0.624500;,
  0.379396;0.658146;,
  0.332591;0.664866;,
  0.332515;0.664877;,
  0.309104;0.668238;,
  0.276578;0.672907;,
  0.293146;0.278357;,
  0.000000;0.252541;,
  0.000000;0.000000;,
  0.295317;0.000000;,
  0.570861;0.000000;,
  0.523984;0.298686;,
  0.000000;0.295317;,
  0.239041;0.000000;,
  0.266851;0.333627;,
  0.287106;0.576616;,
  0.000000;0.570861;,
  0.852178;0.417660;,
  0.816064;0.000000;,
  1.000000;0.438882;,
  1.000000;0.590903;,
  0.866927;0.588236;,
  0.266851;0.333627;,
  0.387680;0.000000;,
  0.390495;0.351378;,
  0.392316;0.578724;,
  0.287106;0.576615;,
  0.293124;0.363213;,
  0.293146;0.278357;,
  0.561118;0.000000;,
  0.409097;0.000000;,
  0.546692;0.000000;,
  0.527801;0.371091;,
  0.517104;0.581225;,
  0.769285;0.405760;,
  0.785588;0.000000;,
  0.762038;0.586134;,
  0.693882;0.394934;,
  0.726345;0.000000;,
  0.678304;0.584456;,
  0.600971;0.382938;,
  0.624104;0.000000;,
  0.588888;0.582949;,
  0.749061;0.318507;,
  0.738957;0.395874;,
  0.740029;0.411258;,
  0.310848;0.323422;,
  0.338538;0.196499;,
  0.674900;0.368048;,
  0.699351;0.314129;;
 }
}

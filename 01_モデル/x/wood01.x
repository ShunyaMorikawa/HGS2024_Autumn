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
 92;
 -92.48338;449.47520;-13.41432;,
 92.48338;449.47520;-13.41432;,
 92.48338;-449.47520;-13.41432;,
 -92.48338;-449.47520;-13.41432;,
 92.48338;449.47520;-13.41432;,
 92.48338;449.47520;12.31842;,
 92.48338;-449.47520;12.31842;,
 92.48338;-449.47520;-13.41432;,
 92.48338;449.47520;12.31842;,
 -92.48338;449.47520;12.31842;,
 -92.48338;-449.47520;12.31842;,
 92.48338;-449.47520;12.31842;,
 -92.48338;449.47520;12.31842;,
 -92.48338;449.47520;-13.41432;,
 -92.48338;-449.47520;-13.41432;,
 -92.48338;-449.47520;12.31842;,
 92.48338;449.47520;-13.41432;,
 -92.48338;449.47520;-13.41432;,
 -92.48338;-449.47520;-13.41432;,
 92.48338;-449.47520;-13.41432;,
 -92.48338;449.47520;-13.41432;,
 92.48338;449.47520;-13.41432;,
 92.48338;-449.47520;-13.41432;,
 -92.48338;-449.47520;-13.41432;,
 92.48338;449.47520;-13.41432;,
 92.48338;449.47520;12.31842;,
 92.48338;-449.47520;12.31842;,
 92.48338;-449.47520;-13.41432;,
 92.48338;449.47520;12.31842;,
 -92.48338;449.47520;12.31842;,
 -92.48338;-449.47520;12.31842;,
 92.48338;-449.47520;12.31842;,
 -92.48338;449.47520;12.31842;,
 -92.48338;449.47520;-13.41432;,
 -92.48338;-449.47520;-13.41432;,
 -92.48338;-449.47520;12.31842;,
 92.48338;449.47520;-13.41432;,
 -92.48338;449.47520;-13.41432;,
 -92.48338;-449.47520;-13.41432;,
 92.48338;-449.47520;-13.41432;,
 0.00000;0.00000;-10.00000;,
 0.00000;20.00000;0.00000;,
 7.07107;0.00000;-7.07107;,
 0.00000;20.00000;0.00000;,
 10.00000;0.00000;0.00000;,
 0.00000;20.00000;0.00000;,
 7.07107;0.00000;7.07107;,
 0.00000;20.00000;0.00000;,
 -0.00000;0.00000;10.00000;,
 0.00000;20.00000;0.00000;,
 -7.07107;0.00000;7.07107;,
 0.00000;20.00000;0.00000;,
 -10.00000;0.00000;-0.00000;,
 0.00000;20.00000;0.00000;,
 -7.07107;0.00000;-7.07107;,
 0.00000;20.00000;0.00000;,
 0.00000;0.00000;-10.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;-10.00000;,
 7.07107;0.00000;-7.07107;,
 10.00000;0.00000;0.00000;,
 7.07107;0.00000;7.07107;,
 -0.00000;0.00000;10.00000;,
 -7.07107;0.00000;7.07107;,
 -10.00000;0.00000;-0.00000;,
 -7.07107;0.00000;-7.07107;,
 0.00000;214.32002;-102.18450;,
 0.00000;1015.84357;0.00000;,
 283.38113;214.32002;-72.25534;,
 0.00000;1015.84357;0.00000;,
 400.76148;214.32002;0.00000;,
 0.00000;1015.84357;0.00000;,
 283.38113;214.32002;72.25534;,
 0.00000;1015.84357;0.00000;,
 -0.00004;214.32002;102.18450;,
 0.00000;1015.84357;0.00000;,
 -283.38116;214.32002;72.25532;,
 0.00000;1015.84357;0.00000;,
 -400.76148;214.32002;-0.00000;,
 0.00000;1015.84357;0.00000;,
 -283.38116;214.32002;-72.25534;,
 0.00000;1015.84357;0.00000;,
 0.00000;214.32002;-102.18450;,
 0.00000;214.32002;0.00000;,
 0.00000;214.32002;-102.18450;,
 283.38113;214.32002;-72.25534;,
 400.76148;214.32002;0.00000;,
 283.38113;214.32002;72.25534;,
 -0.00004;214.32002;102.18450;,
 -283.38116;214.32002;72.25532;,
 -400.76148;214.32002;-0.00000;,
 -283.38116;214.32002;-72.25534;;
 
 44;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 3;40,41,42;,
 3;42,43,44;,
 3;44,45,46;,
 3;46,47,48;,
 3;48,49,50;,
 3;50,51,52;,
 3;52,53,54;,
 3;54,55,56;,
 3;57,58,59;,
 3;57,59,60;,
 3;57,60,61;,
 3;57,61,62;,
 3;57,62,63;,
 3;57,63,64;,
 3;57,64,65;,
 3;57,65,58;,
 3;66,67,68;,
 3;68,69,70;,
 3;70,71,72;,
 3;72,73,74;,
 3;74,75,76;,
 3;76,77,78;,
 3;78,79,80;,
 3;80,81,82;,
 3;83,84,85;,
 3;83,85,86;,
 3;83,86,87;,
 3;83,87,88;,
 3;83,88,89;,
 3;83,89,90;,
 3;83,90,91;,
 3;83,91,84;;
 
 MeshMaterialList {
  2;
  44;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\wood.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\leaf.png";
   }
  }
 }
 MeshNormals {
  27;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.447214;-0.894427;,
  0.632455;0.447214;-0.632455;,
  0.894427;0.447214;0.000000;,
  0.632456;0.447214;0.632456;,
  -0.000000;0.447214;0.894427;,
  -0.632456;0.447214;0.632455;,
  -0.894427;0.447214;-0.000000;,
  -0.632456;0.447214;-0.632455;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.126464;-0.991971;,
  0.313791;0.194717;-0.929312;,
  0.507081;0.253540;-0.823764;,
  0.313791;0.194717;0.929312;,
  -0.000000;0.126464;0.991971;,
  -0.313791;0.194717;0.929312;,
  -0.507081;0.253540;0.823764;,
  -0.313791;0.194717;-0.929312;,
  -0.000000;0.205075;-0.978746;,
  0.507081;0.253540;0.823764;,
  -0.000000;0.205075;0.978746;,
  -0.507081;0.253540;-0.823764;;
  44;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  3;6,7,7;,
  3;7,7,8;,
  3;8,9,9;,
  3;9,9,10;,
  3;10,11,11;,
  3;11,11,12;,
  3;12,13,13;,
  3;13,13,6;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;15,23,16;,
  3;16,23,17;,
  3;24,25,18;,
  3;18,25,19;,
  3;19,25,20;,
  3;20,25,21;,
  3;26,23,22;,
  3;22,23,15;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;,
  3;14,14,14;;
 }
 MeshTextureCoords {
  92;
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}

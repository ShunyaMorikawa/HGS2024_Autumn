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
 119;
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
 0.00000;906.40294;0.00000;,
 91.98775;880.53439;-33.75602;,
 0.00000;880.53439;-47.73820;,
 0.00000;906.40294;0.00000;,
 130.09036;880.53439;0.00000;,
 0.00000;906.40294;0.00000;,
 91.98773;880.53439;33.75602;,
 0.00000;906.40294;0.00000;,
 -0.00001;880.53439;47.73820;,
 0.00000;906.40294;0.00000;,
 -91.98775;880.53439;33.75602;,
 0.00000;906.40294;0.00000;,
 -130.09036;880.53439;0.00000;,
 0.00000;906.40294;0.00000;,
 -91.98775;880.53439;-33.75602;,
 0.00000;906.40294;0.00000;,
 0.00000;880.53439;-47.73820;,
 169.97141;806.84459;-62.37303;,
 0.00000;806.84459;-88.20873;,
 240.37559;806.84459;0.00000;,
 169.97141;806.84459;62.37303;,
 -0.00002;806.84459;88.20873;,
 -169.97141;806.84459;62.37303;,
 -240.37559;806.84459;0.00000;,
 -169.97141;806.84459;-62.37303;,
 0.00000;806.84459;-88.20873;,
 222.07815;696.56393;-81.49436;,
 0.00000;696.56393;-115.25036;,
 314.06570;696.56393;0.00001;,
 222.07815;696.56393;81.49436;,
 -0.00003;696.56393;115.25036;,
 -222.07823;696.56393;81.49435;,
 -314.06570;696.56393;0.00000;,
 -222.07823;696.56393;-81.49435;,
 0.00000;696.56393;-115.25036;,
 240.37559;566.46969;-88.20873;,
 0.00000;566.46969;-124.74607;,
 339.94283;566.46969;0.00001;,
 240.37559;566.46969;88.20873;,
 -0.00003;566.46969;124.74607;,
 -240.37564;566.46969;88.20872;,
 -339.94283;566.46969;0.00000;,
 -240.37564;566.46969;-88.20872;,
 0.00000;566.46969;-124.74607;,
 222.07815;436.37554;-81.49436;,
 0.00000;436.37554;-115.25036;,
 314.06570;436.37554;0.00001;,
 222.07815;436.37554;81.49436;,
 -0.00003;436.37554;115.25036;,
 -222.07823;436.37554;81.49435;,
 -314.06570;436.37554;0.00000;,
 -222.07823;436.37554;-81.49435;,
 0.00000;436.37554;-115.25036;,
 169.97141;326.09520;-62.37303;,
 0.00000;326.09520;-88.20873;,
 240.37559;326.09520;0.00000;,
 169.97141;326.09520;62.37303;,
 -0.00002;326.09520;88.20873;,
 -169.97141;326.09520;62.37303;,
 -240.37559;326.09520;0.00000;,
 -169.97141;326.09520;-62.37303;,
 0.00000;326.09520;-88.20873;,
 91.98775;252.40530;-33.75603;,
 0.00000;252.40530;-47.73820;,
 130.09040;252.40530;0.00000;,
 91.98775;252.40530;33.75603;,
 -0.00001;252.40530;47.73820;,
 -91.98775;252.40530;33.75602;,
 -130.09040;252.40530;0.00000;,
 -91.98775;252.40530;-33.75602;,
 0.00000;252.40530;-47.73820;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;,
 0.00000;226.53631;0.00000;;
 
 76;
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
 3;43,44,41;,
 3;45,46,44;,
 3;47,48,46;,
 3;49,50,48;,
 3;51,52,50;,
 3;53,54,52;,
 3;55,56,54;,
 4;42,41,57,58;,
 4;41,44,59,57;,
 4;44,46,60,59;,
 4;46,48,61,60;,
 4;48,50,62,61;,
 4;50,52,63,62;,
 4;52,54,64,63;,
 4;54,56,65,64;,
 4;58,57,66,67;,
 4;57,59,68,66;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;62,63,72,71;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 4;67,66,75,76;,
 4;66,68,77,75;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;71,72,81,80;,
 4;72,73,82,81;,
 4;73,74,83,82;,
 4;76,75,84,85;,
 4;75,77,86,84;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;79,80,89,88;,
 4;80,81,90,89;,
 4;81,82,91,90;,
 4;82,83,92,91;,
 4;85,84,93,94;,
 4;84,86,95,93;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 4;88,89,98,97;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;91,92,101,100;,
 4;94,93,102,103;,
 4;93,95,104,102;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;97,98,107,106;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 3;103,102,111;,
 3;102,104,112;,
 3;104,105,113;,
 3;105,106,114;,
 3;106,107,115;,
 3;107,108,116;,
 3;108,109,117;,
 3;109,110,118;;
 
 MeshMaterialList {
  2;
  76;
  0,
  0,
  0,
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\obstacle\\wood.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\obstacle\\leaf.png";
   }
  }
 }
 MeshNormals {
  76;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.709738;-0.704465;,
  0.229528;0.799987;-0.554380;,
  0.369575;0.929201;0.000000;,
  0.229528;0.799987;0.554380;,
  -0.000000;0.709738;0.704465;,
  -0.229528;0.799987;0.554380;,
  -0.369575;0.929201;0.000000;,
  -0.229528;0.799987;-0.554380;,
  0.000000;0.362992;-0.931792;,
  0.356710;0.479708;-0.801647;,
  0.547542;0.564110;-0.618044;,
  0.356710;0.479709;0.801647;,
  -0.000000;0.362992;0.931792;,
  -0.356710;0.479709;0.801647;,
  -0.547542;0.564110;0.618044;,
  -0.356710;0.479709;-0.801647;,
  0.000000;0.156046;-0.987750;,
  0.409253;0.221326;-0.885170;,
  0.638365;0.270703;-0.720562;,
  0.409253;0.221326;0.885170;,
  -0.000000;0.156046;0.987750;,
  -0.409253;0.221326;0.885170;,
  -0.638365;0.270703;0.720562;,
  -0.409253;0.221326;-0.885170;,
  0.000000;-0.000000;-1.000000;,
  0.423246;-0.000000;-0.906015;,
  0.663124;-0.000000;-0.748510;,
  0.423246;0.000000;0.906015;,
  -0.000000;-0.000000;1.000000;,
  -0.423246;-0.000000;0.906015;,
  -0.663124;-0.000000;0.748510;,
  -0.423246;-0.000000;-0.906015;,
  0.000000;-0.156046;-0.987750;,
  0.409253;-0.221326;-0.885170;,
  0.638365;-0.270704;-0.720562;,
  0.409253;-0.221326;0.885170;,
  -0.000000;-0.156046;0.987750;,
  -0.409253;-0.221326;0.885170;,
  -0.638365;-0.270704;0.720562;,
  -0.409253;-0.221327;-0.885170;,
  -0.000000;-0.362992;-0.931792;,
  0.356710;-0.479709;-0.801647;,
  0.547542;-0.564110;-0.618044;,
  0.356710;-0.479709;0.801647;,
  -0.000000;-0.362992;0.931792;,
  -0.356710;-0.479709;0.801647;,
  -0.547542;-0.564110;0.618044;,
  -0.356710;-0.479709;-0.801647;,
  -0.000000;-0.709736;-0.704468;,
  0.229529;-0.799985;-0.554383;,
  0.303520;-0.933821;-0.189349;,
  0.229529;-0.799985;0.554383;,
  -0.000000;-0.709736;0.704468;,
  -0.229529;-0.799985;0.554383;,
  -0.303520;-0.933821;0.189349;,
  -0.229529;-0.799985;-0.554383;,
  -0.000000;-1.000000;-0.000000;,
  0.547542;0.564110;0.618044;,
  -0.547542;0.564110;-0.618044;,
  0.638365;0.270703;0.720562;,
  -0.638365;0.270703;-0.720562;,
  0.663123;0.000000;0.748510;,
  -0.663124;-0.000000;-0.748510;,
  0.638365;-0.270704;0.720562;,
  -0.638365;-0.270704;-0.720562;,
  0.547542;-0.564110;0.618044;,
  -0.547542;-0.564110;-0.618044;,
  0.470675;-0.704419;0.531280;,
  -0.470675;-0.704419;-0.531280;;
  76;
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
  3;6,8,7;,
  3;6,9,8;,
  3;6,10,9;,
  3;6,11,10;,
  3;6,12,11;,
  3;6,13,12;,
  3;6,14,13;,
  3;6,7,14;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,10,18,64;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,65;,
  4;14,7,15,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;64,18,26,66;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;65,22,30,67;,
  4;22,15,23,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;66,26,34,68;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;67,30,38,69;,
  4;30,23,31,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;68,34,42,70;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;69,38,46,71;,
  4;38,31,39,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;70,42,50,72;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;71,46,54,73;,
  4;46,39,47,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;72,50,58,74;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;73,54,62,75;,
  4;54,47,55,62;,
  3;55,56,63;,
  3;56,57,63;,
  3;57,58,63;,
  3;58,59,63;,
  3;59,60,63;,
  3;60,61,63;,
  3;61,62,63;,
  3;62,55,63;;
 }
 MeshTextureCoords {
  119;
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
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}

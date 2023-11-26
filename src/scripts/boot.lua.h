////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
// DataAsCode exporter v1.0 - Raw data exported as an array of bytes                  //
//                                                                                    //
// more info and bugs-report:  github.com/raysan5/raylib                              //
// feedback and support:       ray[at]raylib.com                                      //
//                                                                                    //
// Copyright (c) 2022-2023 Ramon Santamaria (@raysan5)                                //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

#define BOOT_DATA_SIZE     4111

static unsigned char BOOT_DATA[BOOT_DATA_SIZE] = { 0x66,
0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x69, 0x6e, 0x69, 0x74, 0x28, 0x29,
0xa, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x2d, 0x20, 0x50, 0x65, 0x73, 0x74, 0x6f, 0x20, 0x6d, 0x6f, 0x64, 0x75, 0x6c, 0x65,
0x73, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f,
0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65,
0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x67, 0x61, 0x6d, 0x65, 0x70, 0x61, 0x64,
0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x67, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x73, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71,
0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6b, 0x65, 0x79, 0x62, 0x6f, 0x61, 0x72, 0x64,
0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28,
0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6d, 0x6f, 0x75, 0x73, 0x65, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72,
0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d,
0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x2d, 0x20, 0x53,
0x74, 0x61, 0x74, 0x65, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x73, 0x74, 0x61, 0x74, 0x65,
0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x73, 0x74,
0x61, 0x74, 0x65, 0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x2d, 0x20, 0x4c, 0x75, 0x61, 0x20, 0x6c, 0x69,
0x62, 0x72, 0x61, 0x72, 0x69, 0x65, 0x73, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x61, 0x73,
0x74, 0x61, 0x72, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x61, 0x73, 0x74, 0x61, 0x72,
0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x20,
0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x62, 0x72, 0x69, 0x6e, 0x65, 0x76, 0x65, 0x63, 0x74,
0x6f, 0x72, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x63, 0x6f, 0x6c, 0x6c, 0x69,
0x73, 0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x62, 0x75, 0x6d, 0x70,
0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x4f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x20,
0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x69, 0x63, 0x22, 0x29,
0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x74, 0x77, 0x65, 0x65, 0x6e, 0x20, 0x3d, 0x20, 0x72,
0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x66, 0x6c, 0x75, 0x78, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70,
0x65, 0x73, 0x74, 0x6f, 0x2e, 0x69, 0x6e, 0x73, 0x70, 0x65, 0x63, 0x74, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69,
0x72, 0x65, 0x28, 0x22, 0x69, 0x6e, 0x73, 0x70, 0x65, 0x63, 0x74, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65,
0x73, 0x74, 0x6f, 0x2e, 0x6a, 0x73, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22,
0x6a, 0x73, 0x6f, 0x6e, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x75, 0x74, 0x69,
0x6c, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x6c, 0x75, 0x6d, 0x65, 0x22, 0x29, 0xa,
0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x73, 0x69, 0x67, 0x6e, 0x61, 0x6c, 0x20, 0x3d, 0x20, 0x72,
0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x73, 0x69, 0x67, 0x6e, 0x61, 0x6c, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20,
0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x74, 0x69, 0x6d, 0x65, 0x72, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69,
0x72, 0x65, 0x28, 0x22, 0x74, 0x69, 0x63, 0x6b, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f,
0x2e, 0x65, 0x63, 0x73, 0x20, 0x3d, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x74, 0x69, 0x6e, 0x79,
0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x2d, 0x20, 0x4c, 0x75, 0x61, 0x73, 0x6f, 0x63, 0x6b, 0x65, 0x74,
0x20, 0x69, 0x73, 0x20, 0x6c, 0x65, 0x66, 0x74, 0x20, 0x61, 0x73, 0x20, 0x69, 0x73, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x6e,
0x6f, 0x77, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74,
0x20, 0x3d, 0x20, 0x61, 0x72, 0x67, 0x5b, 0x31, 0x5d, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20,
0x74, 0x65, 0x6d, 0x70, 0x44, 0x69, 0x72, 0x20, 0x3d, 0x20, 0x6f, 0x73, 0x2e, 0x67, 0x65, 0x74, 0x65, 0x6e, 0x76, 0x28,
0x22, 0x54, 0x45, 0x4d, 0x50, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x6c, 0x75,
0x61, 0x63, 0x68, 0x65, 0x63, 0x6b, 0x50, 0x61, 0x74, 0x68, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x6d, 0x70, 0x44, 0x69, 0x72,
0x20, 0x2e, 0x2e, 0x20, 0x22, 0x5c, 0x5c, 0x6c, 0x75, 0x61, 0x63, 0x68, 0x65, 0x63, 0x6b, 0x2e, 0x65, 0x78, 0x65, 0x22,
0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x20,
0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x28, 0x22,
0x4e, 0x6f, 0x20, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x20, 0x73, 0x70, 0x65, 0x63, 0x69, 0x66, 0x69, 0x65, 0x64, 0x21,
0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61,
0x6c, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x20, 0x3d, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73,
0x79, 0x73, 0x74, 0x65, 0x6d, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x45, 0x78, 0x69, 0x73, 0x74, 0x73, 0x28, 0x74, 0x61, 0x72,
0x67, 0x65, 0x74, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x64, 0x69, 0x72, 0x65, 0x63,
0x74, 0x6f, 0x72, 0x79, 0x20, 0x3d, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x79, 0x73,
0x74, 0x65, 0x6d, 0x2e, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x79, 0x45, 0x78, 0x69, 0x73, 0x74, 0x73, 0x28,
0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x6e, 0x6f, 0x74, 0x20,
0x66, 0x69, 0x6c, 0x65, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x6f,
0x72, 0x79, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x72, 0x72, 0x6f,
0x72, 0x28, 0x22, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x20, 0x64, 0x6f, 0x65, 0x73, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x65,
0x78, 0x69, 0x73, 0x74, 0x21, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20,
0x20, 0x69, 0x66, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x6f,
0x72, 0x79, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x66, 0x69, 0x6c, 0x65,
0x20, 0x3d, 0x20, 0x66, 0x61, 0x6c, 0x73, 0x65, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20,
0x20, 0x20, 0x69, 0x66, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x70, 0x65,
0x73, 0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x2e, 0x69, 0x73, 0x46, 0x69, 0x6c,
0x65, 0x45, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e, 0x28, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x2c, 0x20, 0x22,
0x2e, 0x6c, 0x75, 0x61, 0x22, 0x29, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x65, 0x72, 0x72, 0x6f, 0x72, 0x28, 0x22, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x20, 0x69, 0x73, 0x20, 0x6e, 0x6f, 0x74,
0x20, 0x61, 0x20, 0x6c, 0x75, 0x61, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x21, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65,
0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x79,
0x20, 0x61, 0x6e, 0x64, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73,
0x79, 0x73, 0x74, 0x65, 0x6d, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x45, 0x78, 0x69, 0x73, 0x74, 0x73, 0x28, 0x74, 0x61, 0x72,
0x67, 0x65, 0x74, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2f, 0x6d, 0x61, 0x69, 0x6e, 0x2e, 0x6c, 0x75, 0x61, 0x22, 0x29, 0x20,
0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x28, 0x22,
0x4e, 0x6f, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x2e, 0x6c, 0x75, 0x61, 0x20, 0x66, 0x6f, 0x75, 0x6e, 0x64, 0x21, 0x22, 0x29,
0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x74, 0x65, 0x6d,
0x70, 0x44, 0x69, 0x72, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73,
0x79, 0x73, 0x74, 0x65, 0x6d, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x45, 0x78, 0x69, 0x73, 0x74, 0x73, 0x28, 0x6c, 0x75, 0x61,
0x63, 0x68, 0x65, 0x63, 0x6b, 0x50, 0x61, 0x74, 0x68, 0x29, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x68, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x20, 0x3d, 0x20, 0x69,
0x6f, 0x2e, 0x70, 0x6f, 0x70, 0x65, 0x6e, 0x28, 0x6c, 0x75, 0x61, 0x63, 0x68, 0x65, 0x63, 0x6b, 0x50, 0x61, 0x74, 0x68,
0x20, 0x2e, 0x2e, 0x20, 0x22, 0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x20, 0x2e, 0x2e,
0x20, 0x22, 0x20, 0x2d, 0x2d, 0x67, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x73, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x22, 0x29,
0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x6f, 0x75, 0x74, 0x70, 0x75,
0x74, 0x20, 0x3d, 0x20, 0x68, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x3a, 0x72, 0x65, 0x61, 0x64, 0x28, 0x22, 0x2a, 0x61, 0x22,
0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x3a, 0x63, 0x6c, 0x6f,
0x73, 0x65, 0x28, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20,
0x77, 0x61, 0x72, 0x6e, 0x69, 0x6e, 0x67, 0x73, 0x2c, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x73, 0x2c, 0x20, 0x6d, 0x65,
0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x3d, 0x20, 0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x3a, 0x6d, 0x61, 0x74, 0x63, 0x68,
0x28, 0x22, 0x54, 0x6f, 0x74, 0x61, 0x6c, 0x3a, 0x20, 0x28, 0x25, 0x64, 0x2b, 0x29, 0x20, 0x77, 0x61, 0x72, 0x6e, 0x69,
0x6e, 0x67, 0x3f, 0x73, 0x3f, 0x20, 0x2f, 0x20, 0x28, 0x25, 0x64, 0x2b, 0x29, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x3f,
0x73, 0x3f, 0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x74, 0x6f, 0x6e,
0x75, 0x6d, 0x62, 0x65, 0x72, 0x28, 0x77, 0x61, 0x72, 0x6e, 0x69, 0x6e, 0x67, 0x73, 0x29, 0x20, 0x3e, 0x20, 0x30, 0x20,
0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73,
0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x77, 0x61, 0x72, 0x6e, 0x28, 0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x29, 0xa,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x69, 0x66, 0x20, 0x74, 0x6f, 0x6e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x28, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x73, 0x29,
0x20, 0x3e, 0x20, 0x30, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x28, 0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20,
0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x22, 0x77, 0x61,
0x72, 0x6e, 0x22, 0x29, 0x20, 0x2d, 0x2d, 0x20, 0x44, 0x69, 0x73, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x72, 0x61, 0x79, 0x6c,
0x69, 0x62, 0x27, 0x73, 0x20, 0x77, 0x61, 0x6c, 0x6c, 0x20, 0x6f, 0x66, 0x20, 0x69, 0x6e, 0x66, 0x6f, 0x20, 0x6c, 0x6f,
0x67, 0x73, 0x20, 0x3a, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x6d, 0x61, 0x6a,
0x6f, 0x72, 0x2c, 0x20, 0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x2c, 0x20, 0x70, 0x61, 0x74, 0x63, 0x68, 0x2c, 0x20, 0x63, 0x6f,
0x64, 0x65, 0x6e, 0x61, 0x6d, 0x65, 0x20, 0x3d, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x67, 0x65, 0x74, 0x56, 0x65,
0x72, 0x73, 0x69, 0x6f, 0x6e, 0x28, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77,
0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x69, 0x6e, 0x69, 0x74, 0x28, 0x38, 0x30, 0x30, 0x2c, 0x20, 0x36, 0x30, 0x30, 0x2c,
0x20, 0x22, 0x50, 0x65, 0x73, 0x74, 0x6f, 0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x6d, 0x61, 0x6a, 0x6f, 0x72, 0x20, 0x2e,
0x2e, 0x20, 0x22, 0x2e, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2e,
0x22, 0x20, 0x2e, 0x2e, 0x20, 0x70, 0x61, 0x74, 0x63, 0x68, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x20, 0x22, 0x20, 0x2e, 0x2e,
0x20, 0x63, 0x6f, 0x64, 0x65, 0x6e, 0x61, 0x6d, 0x65, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x73, 0x65, 0x74, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x46, 0x50,
0x53, 0x28, 0x36, 0x30, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67,
0x2e, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x22, 0x69, 0x6e, 0x66, 0x6f, 0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20,
0x69, 0x66, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x70, 0x61, 0x74, 0x68, 0x20, 0x3d, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e,
0x66, 0x69, 0x6c, 0x65, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x2e, 0x67, 0x65, 0x74, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74,
0x6f, 0x72, 0x79, 0x50, 0x61, 0x74, 0x68, 0x28, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x2e, 0x70, 0x61, 0x74, 0x68, 0x20, 0x3d, 0x20,
0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x2e, 0x70, 0x61, 0x74, 0x68, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x3b, 0x22, 0x20,
0x2e, 0x2e, 0x20, 0x70, 0x61, 0x74, 0x68, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2f, 0x3f, 0x2e, 0x6c, 0x75, 0x61, 0x22, 0xa,
0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x70, 0x65, 0x73,
0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x2e, 0x67, 0x65, 0x74, 0x46, 0x69, 0x6c,
0x65, 0x4e, 0x61, 0x6d, 0x65, 0x57, 0x69, 0x74, 0x68, 0x6f, 0x75, 0x74, 0x45, 0x78, 0x74, 0x28, 0x74, 0x61, 0x72, 0x67,
0x65, 0x74, 0x29, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6c, 0x73, 0x65, 0x69, 0x66, 0x20, 0x64, 0x69, 0x72, 0x65,
0x63, 0x74, 0x6f, 0x72, 0x79, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,
0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x2e, 0x70, 0x61, 0x74, 0x68, 0x20, 0x3d, 0x20, 0x70, 0x61, 0x63, 0x6b, 0x61, 0x67,
0x65, 0x2e, 0x70, 0x61, 0x74, 0x68, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x3b, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x74, 0x61, 0x72,
0x67, 0x65, 0x74, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2f, 0x3f, 0x2e, 0x6c, 0x75, 0x61, 0x22, 0xa, 0xa, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x6d, 0x61, 0x69, 0x6e, 0x22, 0x29,
0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x66, 0x75, 0x6e, 0x63, 0x74, 0x69,
0x6f, 0x6e, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x72, 0x75, 0x6e, 0x28, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69,
0x66, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x73, 0x74, 0x61, 0x74, 0x65, 0x2e, 0x72, 0x65,
0x67, 0x69, 0x73, 0x74, 0x65, 0x72, 0x45, 0x76, 0x65, 0x6e, 0x74, 0x73, 0x28, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x73, 0x74, 0x61, 0x74, 0x65, 0x2e, 0x73, 0x77, 0x69, 0x74, 0x63,
0x68, 0x28, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6d, 0x61, 0x69, 0x6e, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e,
0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x77, 0x68, 0x69, 0x6c, 0x65, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x70, 0x65, 0x73,
0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x73, 0x68, 0x6f, 0x75, 0x6c, 0x64, 0x43, 0x6c, 0x6f, 0x73,
0x65, 0x28, 0x29, 0x20, 0x64, 0x6f, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
0x20, 0x64, 0x74, 0x20, 0x3d, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x67,
0x65, 0x74, 0x44, 0x65, 0x6c, 0x74, 0x61, 0x28, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,
0x65, 0x73, 0x74, 0x6f, 0x2e, 0x74, 0x77, 0x65, 0x65, 0x6e, 0x2e, 0x75, 0x70, 0x64, 0x61, 0x74, 0x65, 0x28, 0x64, 0x74,
0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x74, 0x69, 0x6d, 0x65,
0x72, 0x2e, 0x75, 0x70, 0x64, 0x61, 0x74, 0x65, 0x28, 0x64, 0x74, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x69, 0x66, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x75, 0x70, 0x64, 0x61, 0x74, 0x65, 0x20, 0x74, 0x68,
0x65, 0x6e, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x75, 0x70, 0x64, 0x61, 0x74, 0x65, 0x28, 0x64, 0x74, 0x29, 0x20,
0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77,
0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x62, 0x65, 0x67, 0x69, 0x6e, 0x44, 0x72, 0x61, 0x77, 0x69, 0x6e, 0x67, 0x28, 0x29,
0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x67, 0x72, 0x61, 0x70,
0x68, 0x69, 0x63, 0x73, 0x2e, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x28, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x69, 0x66, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x64, 0x72, 0x61, 0x77, 0x20, 0x74, 0x68, 0x65, 0x6e,
0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x64, 0x72, 0x61, 0x77, 0x28, 0x29, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e,
0x65, 0x6e, 0x64, 0x44, 0x72, 0x61, 0x77, 0x69, 0x6e, 0x67, 0x28, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64,
0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x6c, 0x65, 0x76, 0x65,
0x6c, 0x28, 0x22, 0x77, 0x61, 0x72, 0x6e, 0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f,
0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0x28, 0x29, 0xa, 0x65, 0x6e, 0x64, 0xa,
0xa, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x66, 0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x65, 0x72, 0x72, 0x6f,
0x72, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x28, 0x6d, 0x73, 0x67, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65,
0x73, 0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x28, 0x6d, 0x73, 0x67, 0x29, 0xa, 0xa,
0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e,
0x64, 0x6f, 0x77, 0x2e, 0x69, 0x73, 0x52, 0x65, 0x61, 0x64, 0x79, 0x28, 0x29, 0x20, 0x74, 0x68, 0x65, 0x6e, 0xa, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x6c, 0x65, 0x76,
0x65, 0x6c, 0x28, 0x22, 0x77, 0x61, 0x72, 0x6e, 0x22, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x6d, 0x61, 0x6a, 0x6f, 0x72, 0x2c, 0x20, 0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x2c, 0x20,
0x70, 0x61, 0x74, 0x63, 0x68, 0x2c, 0x20, 0x63, 0x6f, 0x64, 0x65, 0x6e, 0x61, 0x6d, 0x65, 0x20, 0x3d, 0x20, 0x70, 0x65,
0x73, 0x74, 0x6f, 0x2e, 0x67, 0x65, 0x74, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x28, 0x29, 0xa, 0xa, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x69,
0x6e, 0x69, 0x74, 0x28, 0x38, 0x30, 0x30, 0x2c, 0x20, 0x36, 0x30, 0x30, 0x2c, 0x20, 0x22, 0x50, 0x65, 0x73, 0x74, 0x6f,
0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x6d, 0x61, 0x6a, 0x6f, 0x72, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2e, 0x22, 0x20, 0x2e,
0x2e, 0x20, 0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2e, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x70, 0x61,
0x74, 0x63, 0x68, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x63, 0x6f, 0x64, 0x65, 0x6e, 0x61,
0x6d, 0x65, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69,
0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x73, 0x65, 0x74, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x46, 0x50, 0x53, 0x28, 0x36, 0x30,
0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x6c, 0x6f, 0x67,
0x2e, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x22, 0x69, 0x6e, 0x66, 0x6f, 0x22, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65,
0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x77, 0x68, 0x69, 0x6c, 0x65, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x70, 0x65,
0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x73, 0x68, 0x6f, 0x75, 0x6c, 0x64, 0x43, 0x6c, 0x6f,
0x73, 0x65, 0x28, 0x29, 0x20, 0x64, 0x6f, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x62, 0x65, 0x67, 0x69, 0x6e, 0x44, 0x72, 0x61, 0x77, 0x69, 0x6e,
0x67, 0x28, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x67,
0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x73, 0x2e, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x28, 0x31, 0x31, 0x39, 0x2c, 0x20, 0x31,
0x37, 0x33, 0x2c, 0x20, 0x31, 0x32, 0x30, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65,
0x73, 0x74, 0x6f, 0x2e, 0x67, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x73, 0x2e, 0x74, 0x65, 0x78, 0x74, 0x28, 0x22, 0x45,
0x72, 0x72, 0x6f, 0x72, 0x22, 0x2c, 0x20, 0x31, 0x30, 0x2c, 0x20, 0x31, 0x30, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x67, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x73, 0x2e, 0x77, 0x70,
0x72, 0x69, 0x6e, 0x74, 0x28, 0x6d, 0x73, 0x67, 0x2c, 0x20, 0x31, 0x30, 0x2c, 0x20, 0x35, 0x30, 0x2c, 0x20, 0x37, 0x38,
0x30, 0x2c, 0x20, 0x36, 0x30, 0x30, 0x29, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73,
0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x65, 0x6e, 0x64, 0x44, 0x72, 0x61, 0x77, 0x69, 0x6e, 0x67,
0x28, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x22, 0x77, 0x61, 0x72, 0x6e, 0x22, 0x29, 0xa,
0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x63, 0x6c,
0x6f, 0x73, 0x65, 0x28, 0x29, 0xa, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x66, 0x75,
0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x28, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x72,
0x65, 0x73, 0x75, 0x6c, 0x74, 0x20, 0x3d, 0x20, 0x78, 0x70, 0x63, 0x61, 0x6c, 0x6c, 0x28, 0x70, 0x65, 0x73, 0x74, 0x6f,
0x2e, 0x69, 0x6e, 0x69, 0x74, 0x2c, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x29,
0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x20, 0x74,
0x68, 0x65, 0x6e, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x31, 0x20, 0x65, 0x6e, 0x64, 0xa, 0x20, 0x20, 0x20,
0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x2c, 0x20, 0x72, 0x65, 0x74, 0x76, 0x61,
0x6c, 0x20, 0x3d, 0x20, 0x78, 0x70, 0x63, 0x61, 0x6c, 0x6c, 0x28, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x72, 0x75, 0x6e,
0x2c, 0x20, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x29, 0xa, 0x20, 0x20, 0x20, 0x20,
0x69, 0x66, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x20, 0x74, 0x68, 0x65, 0x6e, 0x20, 0x72,
0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x31, 0x20, 0x65, 0x6e, 0x64, 0xa, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74,
0x75, 0x72, 0x6e, 0x20, 0x74, 0x6f, 0x6e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x28, 0x72, 0x65, 0x74, 0x76, 0x61, 0x6c, 0x29,
0x20, 0x6f, 0x72, 0x20, 0x30, 0xa, 0x65, 0x6e, 0x64, 0xa };

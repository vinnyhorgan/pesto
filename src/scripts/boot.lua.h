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

static unsigned char BOOT_DATA[830] = { 0x66,
0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x69, 0x6e, 0x69, 0x74, 0x28, 0x29,
0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f,
0x2e, 0x6c, 0x6f, 0x67, 0x22, 0x29, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28,
0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x22, 0x29, 0xd,
0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x28, 0x22, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e,
0x77, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x22, 0x29, 0xd, 0xa, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74,
0x6f, 0x2e, 0x6c, 0x6f, 0x67, 0x2e, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x22, 0x77, 0x61, 0x72, 0x6e, 0x22, 0x29, 0xd,
0xa, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x6d, 0x61, 0x6a, 0x6f, 0x72, 0x2c, 0x20,
0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x2c, 0x20, 0x70, 0x61, 0x74, 0x63, 0x68, 0x2c, 0x20, 0x63, 0x6f, 0x64, 0x65, 0x6e, 0x61,
0x6d, 0x65, 0x20, 0x3d, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x67, 0x65, 0x74, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f,
0x6e, 0x28, 0x29, 0xd, 0xa, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e,
0x64, 0x6f, 0x77, 0x2e, 0x69, 0x6e, 0x69, 0x74, 0x28, 0x38, 0x30, 0x30, 0x2c, 0x20, 0x36, 0x30, 0x30, 0x2c, 0x20, 0x22,
0x50, 0x65, 0x73, 0x74, 0x6f, 0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x6d, 0x61, 0x6a, 0x6f, 0x72, 0x20, 0x2e, 0x2e, 0x20,
0x22, 0x2e, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x6d, 0x69, 0x6e, 0x6f, 0x72, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x2e, 0x22, 0x20,
0x2e, 0x2e, 0x20, 0x70, 0x61, 0x74, 0x63, 0x68, 0x20, 0x2e, 0x2e, 0x20, 0x22, 0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x63,
0x6f, 0x64, 0x65, 0x6e, 0x61, 0x6d, 0x65, 0x29, 0xd, 0xa, 0x65, 0x6e, 0x64, 0xd, 0xa, 0xd, 0xa, 0x66, 0x75, 0x6e,
0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x72, 0x75, 0x6e, 0x28, 0x29, 0xd, 0xa, 0x20,
0x20, 0x20, 0x20, 0x77, 0x68, 0x69, 0x6c, 0x65, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77,
0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x73, 0x68, 0x6f, 0x75, 0x6c, 0x64, 0x43, 0x6c, 0x6f, 0x73, 0x65, 0x28, 0x29, 0x20,
0x64, 0x6f, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69,
0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x62, 0x65, 0x67, 0x69, 0x6e, 0x44, 0x72, 0x61, 0x77, 0x69, 0x6e, 0x67, 0x28, 0x29, 0xd,
0xa, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77, 0x69, 0x6e,
0x64, 0x6f, 0x77, 0x2e, 0x65, 0x6e, 0x64, 0x44, 0x72, 0x61, 0x77, 0x69, 0x6e, 0x67, 0x28, 0x29, 0xd, 0xa, 0x20, 0x20,
0x20, 0x20, 0x65, 0x6e, 0x64, 0xd, 0xa, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x77,
0x69, 0x6e, 0x64, 0x6f, 0x77, 0x2e, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0x28, 0x29, 0xd, 0xa, 0x65, 0x6e, 0x64, 0xd, 0xa,
0xd, 0xa, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x66, 0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x65, 0x72, 0x72,
0x6f, 0x72, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x28, 0x6d, 0x73, 0x67, 0x29, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20,
0x70, 0x72, 0x69, 0x6e, 0x74, 0x28, 0x22, 0x45, 0x72, 0x72, 0x6f, 0x72, 0x3a, 0x20, 0x22, 0x20, 0x2e, 0x2e, 0x20, 0x74,
0x6f, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x28, 0x6d, 0x73, 0x67, 0x29, 0x29, 0xd, 0xa, 0x65, 0x6e, 0x64, 0xd, 0xa,
0xd, 0xa, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x66, 0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x28, 0x29, 0xd,
0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x20, 0x3d, 0x20,
0x78, 0x70, 0x63, 0x61, 0x6c, 0x6c, 0x28, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x69, 0x6e, 0x69, 0x74, 0x2c, 0x20, 0x65,
0x72, 0x72, 0x6f, 0x72, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x29, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66,
0x20, 0x6e, 0x6f, 0x74, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x20, 0x74, 0x68, 0x65, 0x6e, 0x20, 0x72, 0x65, 0x74,
0x75, 0x72, 0x6e, 0x20, 0x31, 0x20, 0x65, 0x6e, 0x64, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x6f, 0x63, 0x61, 0x6c,
0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x2c, 0x20, 0x72, 0x65, 0x74, 0x76, 0x61, 0x6c, 0x20, 0x3d, 0x20, 0x78, 0x70,
0x63, 0x61, 0x6c, 0x6c, 0x28, 0x70, 0x65, 0x73, 0x74, 0x6f, 0x2e, 0x72, 0x75, 0x6e, 0x2c, 0x20, 0x65, 0x72, 0x72, 0x6f,
0x72, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x29, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x6e, 0x6f,
0x74, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x20, 0x74, 0x68, 0x65, 0x6e, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e,
0x20, 0x31, 0x20, 0x65, 0x6e, 0x64, 0xd, 0xa, 0xd, 0xa, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e,
0x20, 0x74, 0x6f, 0x6e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x28, 0x72, 0x65, 0x74, 0x76, 0x61, 0x6c, 0x29, 0x20, 0x6f, 0x72,
0x20, 0x30, 0xd, 0xa, 0x65, 0x6e, 0x64, 0xd, 0xa };

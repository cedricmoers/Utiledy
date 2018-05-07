// GammaCorrectedLED.h

#include "c:\Users\Cedric\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266\Arduino.h"

#ifndef _UPDATEABLELED_h
#define _UPDATEABLELED_h

//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "arduino.h"
//#else
//	#include "WProgram.h"
//#endif
//
//

//Set for which resolution the library needs to be compiled.
#define UPDATEABLE_LED_BRIGHTNESS_RES_12BIT
//#define UPDATEABLE_LED_BRIGHTNESS_RES_10BIT
//#define UPDATEABLE_LED_BRIGHTNESS_RES_8BIT

#ifdef UPDATEABLE_LED_BRIGHTNESS_RES_12BIT
#define BRIGHTNESS_TYPE uint16_t 
#define BRIGHTNESS_TYPE_MAX 4095
#define BRIGHTNESS_TYPE_MIN 0
#elif defined UPDATEABLE_LED_BRIGHTNESS_RES_10BIT
#define BRIGHTNESS_TYPE uint16_t 
#define BRIGHTNESS_TYPE_MAX 1023
#define BRIGHTNESS_TYPE_MIN 0
#elif defined UPDATEABLE_LED_BRIGHTNESS_RES_8BIT
#define BRIGHTNESS_TYPE uint8_t 
#define BRIGHTNESS_TYPE_MAX 255
#define BRIGHTNESS_TYPE_MIN 0
#else  //Default = 8 bit
#define BRIGHTNESS_TYPE uint8_t 
#define BRIGHTNESS_TYPE_MAX 255
#define BRIGHTNESS_TYPE_MIN 0
#endif


//Set the gamma correction based upon the resolution. TODO:: Check why PROGMEM crashes ESP
#ifdef UPDATEABLE_LED_BRIGHTNESS_RES_12BIT

const uint16_t gammaCorrectionLookupTable[] = {
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
	1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
	1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
	2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
	2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
	3,   3,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
	4,   4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,
	5,   5,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,
	7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,
	8,   8,   8,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,   9,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,
	10,  10,  10,  10,  10,  10,  10,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  12,  12,  12,  12,  12,  12,  12,  12,  12,
	12,  12,  12,  12,  12,  12,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,
	14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  17,  17,  17,  17,
	17,  17,  17,  17,  17,  17,  17,  17,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  20,
	20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  21,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  23,
	23,  23,  23,  23,  23,  23,  23,  23,  23,  24,  24,  24,  24,  24,  24,  24,  24,  24,  24,  25,  25,  25,  25,  25,  25,  25,  25,  25,  26,  26,  26,  26,
	26,  26,  26,  26,  26,  27,  27,  27,  27,  27,  27,  27,  27,  27,  28,  28,  28,  28,  28,  28,  28,  28,  28,  29,  29,  29,  29,  29,  29,  29,  29,  29,
	30,  30,  30,  30,  30,  30,  30,  30,  31,  31,  31,  31,  31,  31,  31,  31,  32,  32,  32,  32,  32,  32,  32,  32,  33,  33,  33,  33,  33,  33,  33,  33,
	34,  34,  34,  34,  34,  34,  34,  34,  35,  35,  35,  35,  35,  35,  35,  35,  36,  36,  36,  36,  36,  36,  36,  37,  37,  37,  37,  37,  37,  37,  37,  38,
	38,  38,  38,  38,  38,  38,  39,  39,  39,  39,  39,  39,  39,  40,  40,  40,  40,  40,  40,  40,  41,  41,  41,  41,  41,  41,  41,  42,  42,  42,  42,  42,
	42,  42,  43,  43,  43,  43,  43,  43,  44,  44,  44,  44,  44,  44,  44,  45,  45,  45,  45,  45,  45,  46,  46,  46,  46,  46,  46,  46,  47,  47,  47,  47,
	47,  47,  48,  48,  48,  48,  48,  48,  49,  49,  49,  49,  49,  49,  49,  50,  50,  50,  50,  50,  50,  51,  51,  51,  51,  51,  51,  52,  52,  52,  52,  52,
	53,  53,  53,  53,  53,  53,  54,  54,  54,  54,  54,  54,  55,  55,  55,  55,  55,  55,  56,  56,  56,  56,  56,  57,  57,  57,  57,  57,  57,  58,  58,  58,
	58,  58,  58,  59,  59,  59,  59,  59,  60,  60,  60,  60,  60,  61,  61,  61,  61,  61,  61,  62,  62,  62,  62,  62,  63,  63,  63,  63,  63,  64,  64,  64,
	64,  64,  65,  65,  65,  65,  65,  65,  66,  66,  66,  66,  66,  67,  67,  67,  67,  67,  68,  68,  68,  68,  68,  69,  69,  69,  69,  69,  70,  70,  70,  70,
	71,  71,  71,  71,  71,  72,  72,  72,  72,  72,  73,  73,  73,  73,  73,  74,  74,  74,  74,  74,  75,  75,  75,  75,  76,  76,  76,  76,  76,  77,  77,  77,
	77,  78,  78,  78,  78,  78,  79,  79,  79,  79,  80,  80,  80,  80,  80,  81,  81,  81,  81,  82,  82,  82,  82,  82,  83,  83,  83,  83,  84,  84,  84,  84,
	84,  85,  85,  85,  85,  86,  86,  86,  86,  87,  87,  87,  87,  88,  88,  88,  88,  88,  89,  89,  89,  89,  90,  90,  90,  90,  91,  91,  91,  91,  92,  92,
	92,  92,  93,  93,  93,  93,  94,  94,  94,  94,  95,  95,  95,  95,  96,  96,  96,  96,  97,  97,  97,  97,  98,  98,  98,  98,  99,  99,  99,  99, 100, 100,
	100, 100, 101, 101, 101, 101, 102, 102, 102, 102, 103, 103, 103, 104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 107, 107, 107, 107, 108, 108, 108,
	109, 109, 109, 109, 110, 110, 110, 110, 111, 111, 111, 112, 112, 112, 112, 113, 113, 113, 114, 114, 114, 114, 115, 115, 115, 116, 116, 116, 116, 117, 117, 117,
	117, 118, 118, 118, 119, 119, 119, 120, 120, 120, 120, 121, 121, 121, 122, 122, 122, 122, 123, 123, 123, 124, 124, 124, 124, 125, 125, 125, 126, 126, 126, 127,
	127, 127, 127, 128, 128, 128, 129, 129, 129, 130, 130, 130, 130, 131, 131, 131, 132, 132, 132, 133, 133, 133, 134, 134, 134, 135, 135, 135, 135, 136, 136, 136,
	137, 137, 137, 138, 138, 138, 139, 139, 139, 140, 140, 140, 141, 141, 141, 141, 142, 142, 142, 143, 143, 143, 144, 144, 144, 145, 145, 145, 146, 146, 146, 147,
	147, 147, 148, 148, 148, 149, 149, 149, 150, 150, 150, 151, 151, 151, 152, 152, 152, 153, 153, 153, 154, 154, 154, 155, 155, 155, 156, 156, 156, 157, 157, 157,
	158, 158, 159, 159, 159, 160, 160, 160, 161, 161, 161, 162, 162, 162, 163, 163, 163, 164, 164, 164, 165, 165, 166, 166, 166, 167, 167, 167, 168, 168, 168, 169,
	169, 169, 170, 170, 171, 171, 171, 172, 172, 172, 173, 173, 173, 174, 174, 175, 175, 175, 176, 176, 176, 177, 177, 178, 178, 178, 179, 179, 179, 180, 180, 181,
	181, 181, 182, 182, 182, 183, 183, 184, 184, 184, 185, 185, 185, 186, 186, 187, 187, 187, 188, 188, 189, 189, 189, 190, 190, 190, 191, 191, 192, 192, 192, 193,
	193, 194, 194, 194, 195, 195, 196, 196, 196, 197, 197, 198, 198, 198, 199, 199, 200, 200, 200, 201, 201, 202, 202, 202, 203, 203, 204, 204, 204, 205, 205, 206,
	206, 206, 207, 207, 208, 208, 209, 209, 209, 210, 210, 211, 211, 211, 212, 212, 213, 213, 214, 214, 214, 215, 215, 216, 216, 216, 217, 217, 218, 218, 219, 219,
	219, 220, 220, 221, 221, 222, 222, 222, 223, 223, 224, 224, 225, 225, 225, 226, 226, 227, 227, 228, 228, 229, 229, 229, 230, 230, 231, 231, 232, 232, 233, 233,
	233, 234, 234, 235, 235, 236, 236, 237, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 246, 247, 247,
	248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253, 253, 253, 254, 254, 255, 255, 256, 256, 257, 257, 258, 258, 259, 259, 260, 260, 261, 261, 261, 262, 262,
	263, 263, 264, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 270, 270, 271, 271, 272, 272, 273, 273, 274, 274, 275, 275, 276, 276, 277, 277, 278, 278,
	279, 279, 280, 280, 281, 281, 282, 282, 283, 283, 284, 284, 285, 285, 286, 286, 287, 287, 288, 288, 289, 289, 290, 290, 291, 291, 292, 292, 293, 293, 294, 294,
	295, 295, 296, 296, 297, 297, 298, 298, 299, 299, 300, 300, 301, 302, 302, 303, 303, 304, 304, 305, 305, 306, 306, 307, 307, 308, 308, 309, 309, 310, 311, 311,
	312, 312, 313, 313, 314, 314, 315, 315, 316, 316, 317, 317, 318, 319, 319, 320, 320, 321, 321, 322, 322, 323, 323, 324, 325, 325, 326, 326, 327, 327, 328, 328,
	329, 330, 330, 331, 331, 332, 332, 333, 333, 334, 335, 335, 336, 336, 337, 337, 338, 338, 339, 340, 340, 341, 341, 342, 342, 343, 344, 344, 345, 345, 346, 346,
	347, 348, 348, 349, 349, 350, 350, 351, 352, 352, 353, 353, 354, 355, 355, 356, 356, 357, 357, 358, 359, 359, 360, 360, 361, 362, 362, 363, 363, 364, 364, 365,
	366, 366, 367, 367, 368, 369, 369, 370, 370, 371, 372, 372, 373, 373, 374, 375, 375, 376, 376, 377, 378, 378, 379, 379, 380, 381, 381, 382, 382, 383, 384, 384,
	385, 386, 386, 387, 387, 388, 389, 389, 390, 390, 391, 392, 392, 393, 394, 394, 395, 395, 396, 397, 397, 398, 399, 399, 400, 400, 401, 402, 402, 403, 404, 404,
	405, 405, 406, 407, 407, 408, 409, 409, 410, 411, 411, 412, 412, 413, 414, 414, 415, 416, 416, 417, 418, 418, 419, 420, 420, 421, 422, 422, 423, 423, 424, 425,
	425, 426, 427, 427, 428, 429, 429, 430, 431, 431, 432, 433, 433, 434, 435, 435, 436, 437, 437, 438, 439, 439, 440, 441, 441, 442, 443, 443, 444, 445, 445, 446,
	447, 447, 448, 449, 449, 450, 451, 451, 452, 453, 453, 454, 455, 455, 456, 457, 458, 458, 459, 460, 460, 461, 462, 462, 463, 464, 464, 465, 466, 466, 467, 468,
	469, 469, 470, 471, 471, 472, 473, 473, 474, 475, 476, 476, 477, 478, 478, 479, 480, 480, 481, 482, 483, 483, 484, 485, 485, 486, 487, 488, 488, 489, 490, 490,
	491, 492, 493, 493, 494, 495, 495, 496, 497, 498, 498, 499, 500, 500, 501, 502, 503, 503, 504, 505, 506, 506, 507, 508, 509, 509, 510, 511, 511, 512, 513, 514,
	514, 515, 516, 517, 517, 518, 519, 520, 520, 521, 522, 523, 523, 524, 525, 526, 526, 527, 528, 529, 529, 530, 531, 532, 532, 533, 534, 535, 535, 536, 537, 538,
	538, 539, 540, 541, 541, 542, 543, 544, 544, 545, 546, 547, 548, 548, 549, 550, 551, 551, 552, 553, 554, 554, 555, 556, 557, 558, 558, 559, 560, 561, 561, 562,
	563, 564, 565, 565, 566, 567, 568, 569, 569, 570, 571, 572, 572, 573, 574, 575, 576, 576, 577, 578, 579, 580, 580, 581, 582, 583, 584, 584, 585, 586, 587, 588,
	588, 589, 590, 591, 592, 592, 593, 594, 595, 596, 596, 597, 598, 599, 600, 601, 601, 602, 603, 604, 605, 605, 606, 607, 608, 609, 610, 610, 611, 612, 613, 614,
	614, 615, 616, 617, 618, 619, 619, 620, 621, 622, 623, 624, 624, 625, 626, 627, 628, 629, 630, 630, 631, 632, 633, 634, 635, 635, 636, 637, 638, 639, 640, 640,
	641, 642, 643, 644, 645, 646, 646, 647, 648, 649, 650, 651, 652, 652, 653, 654, 655, 656, 657, 658, 658, 659, 660, 661, 662, 663, 664, 665, 665, 666, 667, 668,
	669, 670, 671, 672, 672, 673, 674, 675, 676, 677, 678, 679, 679, 680, 681, 682, 683, 684, 685, 686, 687, 687, 688, 689, 690, 691, 692, 693, 694, 695, 695, 696,
	697, 698, 699, 700, 701, 702, 703, 704, 704, 705, 706, 707, 708, 709, 710, 711, 712, 713, 714, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 725,
	726, 727, 728, 729, 730, 731, 732, 733, 734, 735, 736, 737, 737, 738, 739, 740, 741, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 751, 752, 753, 754, 755,
	756, 757, 758, 759, 760, 761, 762, 763, 764, 765, 766, 767, 768, 769, 770, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 785, 786,
	787, 788, 789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 800, 801, 802, 803, 804, 805, 806, 807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817,
	818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 831, 832, 833, 834, 835, 836, 837, 838, 839, 840, 841, 842, 843, 844, 845, 846, 847, 848, 849,
	850, 852, 853, 854, 855, 856, 857, 858, 859, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871, 872, 873, 874, 875, 876, 877, 878, 879, 880, 881, 882,
	884, 885, 886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 896, 897, 898, 899, 900, 901, 902, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916,
	917, 918, 919, 921, 922, 923, 924, 925, 926, 927, 928, 929, 930, 931, 932, 933, 935, 936, 937, 938, 939, 940, 941, 942, 943, 944, 945, 947, 948, 949, 950, 951,
	952, 953, 954, 955, 956, 957, 959, 960, 961, 962, 963, 964, 965, 966, 967, 969, 970, 971, 972, 973, 974, 975, 976, 977, 979, 980, 981, 982, 983, 984, 985, 986,
	987, 989, 990, 991, 992, 993, 994, 995, 997, 998, 999,1000,1001,1002,1003,1004,1006,1007,1008,1009,1010,1011,1012,1014,1015,1016,1017,1018,1019,1020,1022,1023,
	1024,1025,1026,1027,1028,1030,1031,1032,1033,1034,1035,1037,1038,1039,1040,1041,1042,1043,1045,1046,1047,1048,1049,1050,1052,1053,1054,1055,1056,1057,1059,1060,
	1061,1062,1063,1065,1066,1067,1068,1069,1070,1072,1073,1074,1075,1076,1078,1079,1080,1081,1082,1083,1085,1086,1087,1088,1089,1091,1092,1093,1094,1095,1097,1098,
	1099,1100,1101,1103,1104,1105,1106,1107,1109,1110,1111,1112,1114,1115,1116,1117,1118,1120,1121,1122,1123,1124,1126,1127,1128,1129,1131,1132,1133,1134,1135,1137,
	1138,1139,1140,1142,1143,1144,1145,1147,1148,1149,1150,1152,1153,1154,1155,1156,1158,1159,1160,1161,1163,1164,1165,1166,1168,1169,1170,1171,1173,1174,1175,1176,
	1178,1179,1180,1181,1183,1184,1185,1187,1188,1189,1190,1192,1193,1194,1195,1197,1198,1199,1200,1202,1203,1204,1206,1207,1208,1209,1211,1212,1213,1215,1216,1217,
	1218,1220,1221,1222,1224,1225,1226,1227,1229,1230,1231,1233,1234,1235,1236,1238,1239,1240,1242,1243,1244,1246,1247,1248,1249,1251,1252,1253,1255,1256,1257,1259,
	1260,1261,1263,1264,1265,1266,1268,1269,1270,1272,1273,1274,1276,1277,1278,1280,1281,1282,1284,1285,1286,1288,1289,1290,1292,1293,1294,1296,1297,1298,1300,1301,
	1302,1304,1305,1306,1308,1309,1310,1312,1313,1314,1316,1317,1319,1320,1321,1323,1324,1325,1327,1328,1329,1331,1332,1333,1335,1336,1338,1339,1340,1342,1343,1344,
	1346,1347,1348,1350,1351,1353,1354,1355,1357,1358,1359,1361,1362,1364,1365,1366,1368,1369,1371,1372,1373,1375,1376,1377,1379,1380,1382,1383,1384,1386,1387,1389,
	1390,1391,1393,1394,1396,1397,1398,1400,1401,1403,1404,1405,1407,1408,1410,1411,1412,1414,1415,1417,1418,1420,1421,1422,1424,1425,1427,1428,1430,1431,1432,1434,
	1435,1437,1438,1439,1441,1442,1444,1445,1447,1448,1450,1451,1452,1454,1455,1457,1458,1460,1461,1462,1464,1465,1467,1468,1470,1471,1473,1474,1476,1477,1478,1480,
	1481,1483,1484,1486,1487,1489,1490,1492,1493,1494,1496,1497,1499,1500,1502,1503,1505,1506,1508,1509,1511,1512,1514,1515,1517,1518,1520,1521,1522,1524,1525,1527,
	1528,1530,1531,1533,1534,1536,1537,1539,1540,1542,1543,1545,1546,1548,1549,1551,1552,1554,1555,1557,1558,1560,1561,1563,1564,1566,1567,1569,1570,1572,1573,1575,
	1576,1578,1579,1581,1583,1584,1586,1587,1589,1590,1592,1593,1595,1596,1598,1599,1601,1602,1604,1605,1607,1608,1610,1612,1613,1615,1616,1618,1619,1621,1622,1624,
	1625,1627,1629,1630,1632,1633,1635,1636,1638,1639,1641,1642,1644,1646,1647,1649,1650,1652,1653,1655,1657,1658,1660,1661,1663,1664,1666,1668,1669,1671,1672,1674,
	1675,1677,1679,1680,1682,1683,1685,1686,1688,1690,1691,1693,1694,1696,1698,1699,1701,1702,1704,1706,1707,1709,1710,1712,1713,1715,1717,1718,1720,1722,1723,1725,
	1726,1728,1730,1731,1733,1734,1736,1738,1739,1741,1742,1744,1746,1747,1749,1751,1752,1754,1755,1757,1759,1760,1762,1764,1765,1767,1768,1770,1772,1773,1775,1777,
	1778,1780,1782,1783,1785,1786,1788,1790,1791,1793,1795,1796,1798,1800,1801,1803,1805,1806,1808,1810,1811,1813,1815,1816,1818,1819,1821,1823,1824,1826,1828,1829,
	1831,1833,1834,1836,1838,1840,1841,1843,1845,1846,1848,1850,1851,1853,1855,1856,1858,1860,1861,1863,1865,1866,1868,1870,1871,1873,1875,1877,1878,1880,1882,1883,
	1885,1887,1888,1890,1892,1894,1895,1897,1899,1900,1902,1904,1906,1907,1909,1911,1912,1914,1916,1918,1919,1921,1923,1924,1926,1928,1930,1931,1933,1935,1937,1938,
	1940,1942,1943,1945,1947,1949,1950,1952,1954,1956,1957,1959,1961,1963,1964,1966,1968,1970,1971,1973,1975,1977,1978,1980,1982,1984,1985,1987,1989,1991,1992,1994,
	1996,1998,1999,2001,2003,2005,2007,2008,2010,2012,2014,2015,2017,2019,2021,2022,2024,2026,2028,2030,2031,2033,2035,2037,2039,2040,2042,2044,2046,2047,2049,2051,
	2053,2055,2056,2058,2060,2062,2064,2065,2067,2069,2071,2073,2075,2076,2078,2080,2082,2084,2085,2087,2089,2091,2093,2094,2096,2098,2100,2102,2104,2105,2107,2109,
	2111,2113,2115,2116,2118,2120,2122,2124,2126,2127,2129,2131,2133,2135,2137,2138,2140,2142,2144,2146,2148,2150,2151,2153,2155,2157,2159,2161,2162,2164,2166,2168,
	2170,2172,2174,2176,2177,2179,2181,2183,2185,2187,2189,2190,2192,2194,2196,2198,2200,2202,2204,2205,2207,2209,2211,2213,2215,2217,2219,2221,2222,2224,2226,2228,
	2230,2232,2234,2236,2238,2239,2241,2243,2245,2247,2249,2251,2253,2255,2257,2259,2260,2262,2264,2266,2268,2270,2272,2274,2276,2278,2280,2282,2283,2285,2287,2289,
	2291,2293,2295,2297,2299,2301,2303,2305,2307,2309,2310,2312,2314,2316,2318,2320,2322,2324,2326,2328,2330,2332,2334,2336,2338,2340,2342,2344,2346,2348,2349,2351,
	2353,2355,2357,2359,2361,2363,2365,2367,2369,2371,2373,2375,2377,2379,2381,2383,2385,2387,2389,2391,2393,2395,2397,2399,2401,2403,2405,2407,2409,2411,2413,2415,
	2417,2419,2421,2423,2425,2427,2429,2431,2433,2435,2437,2439,2441,2443,2445,2447,2449,2451,2453,2455,2457,2459,2461,2463,2465,2467,2469,2471,2473,2475,2477,2479,
	2481,2483,2485,2487,2489,2491,2493,2495,2497,2499,2501,2503,2505,2508,2510,2512,2514,2516,2518,2520,2522,2524,2526,2528,2530,2532,2534,2536,2538,2540,2542,2544,
	2547,2549,2551,2553,2555,2557,2559,2561,2563,2565,2567,2569,2571,2573,2576,2578,2580,2582,2584,2586,2588,2590,2592,2594,2596,2598,2601,2603,2605,2607,2609,2611,
	2613,2615,2617,2619,2622,2624,2626,2628,2630,2632,2634,2636,2638,2640,2643,2645,2647,2649,2651,2653,2655,2657,2660,2662,2664,2666,2668,2670,2672,2674,2677,2679,
	2681,2683,2685,2687,2689,2691,2694,2696,2698,2700,2702,2704,2706,2709,2711,2713,2715,2717,2719,2722,2724,2726,2728,2730,2732,2734,2737,2739,2741,2743,2745,2747,
	2750,2752,2754,2756,2758,2760,2763,2765,2767,2769,2771,2773,2776,2778,2780,2782,2784,2787,2789,2791,2793,2795,2798,2800,2802,2804,2806,2809,2811,2813,2815,2817,
	2820,2822,2824,2826,2828,2831,2833,2835,2837,2839,2842,2844,2846,2848,2850,2853,2855,2857,2859,2862,2864,2866,2868,2870,2873,2875,2877,2879,2882,2884,2886,2888,
	2891,2893,2895,2897,2900,2902,2904,2906,2909,2911,2913,2915,2918,2920,2922,2924,2927,2929,2931,2933,2936,2938,2940,2942,2945,2947,2949,2951,2954,2956,2958,2960,
	2963,2965,2967,2970,2972,2974,2976,2979,2981,2983,2986,2988,2990,2992,2995,2997,2999,3002,3004,3006,3008,3011,3013,3015,3018,3020,3022,3025,3027,3029,3031,3034,
	3036,3038,3041,3043,3045,3048,3050,3052,3055,3057,3059,3062,3064,3066,3069,3071,3073,3076,3078,3080,3083,3085,3087,3090,3092,3094,3097,3099,3101,3104,3106,3108,
	3111,3113,3115,3118,3120,3122,3125,3127,3129,3132,3134,3136,3139,3141,3144,3146,3148,3151,3153,3155,3158,3160,3163,3165,3167,3170,3172,3174,3177,3179,3182,3184,
	3186,3189,3191,3193,3196,3198,3201,3203,3205,3208,3210,3213,3215,3217,3220,3222,3225,3227,3229,3232,3234,3237,3239,3241,3244,3246,3249,3251,3253,3256,3258,3261,
	3263,3266,3268,3270,3273,3275,3278,3280,3283,3285,3287,3290,3292,3295,3297,3300,3302,3304,3307,3309,3312,3314,3317,3319,3322,3324,3326,3329,3331,3334,3336,3339,
	3341,3344,3346,3349,3351,3353,3356,3358,3361,3363,3366,3368,3371,3373,3376,3378,3381,3383,3386,3388,3391,3393,3395,3398,3400,3403,3405,3408,3410,3413,3415,3418,
	3420,3423,3425,3428,3430,3433,3435,3438,3440,3443,3445,3448,3450,3453,3455,3458,3460,3463,3465,3468,3470,3473,3476,3478,3481,3483,3486,3488,3491,3493,3496,3498,
	3501,3503,3506,3508,3511,3513,3516,3519,3521,3524,3526,3529,3531,3534,3536,3539,3541,3544,3547,3549,3552,3554,3557,3559,3562,3564,3567,3570,3572,3575,3577,3580,
	3582,3585,3588,3590,3593,3595,3598,3600,3603,3606,3608,3611,3613,3616,3618,3621,3624,3626,3629,3631,3634,3637,3639,3642,3644,3647,3650,3652,3655,3657,3660,3663,
	3665,3668,3670,3673,3676,3678,3681,3683,3686,3689,3691,3694,3697,3699,3702,3704,3707,3710,3712,3715,3718,3720,3723,3725,3728,3731,3733,3736,3739,3741,3744,3747,
	3749,3752,3755,3757,3760,3762,3765,3768,3770,3773,3776,3778,3781,3784,3786,3789,3792,3794,3797,3800,3802,3805,3808,3810,3813,3816,3818,3821,3824,3826,3829,3832,
	3835,3837,3840,3843,3845,3848,3851,3853,3856,3859,3861,3864,3867,3870,3872,3875,3878,3880,3883,3886,3888,3891,3894,3897,3899,3902,3905,3907,3910,3913,3916,3918,
	3921,3924,3926,3929,3932,3935,3937,3940,3943,3946,3948,3951,3954,3957,3959,3962,3965,3967,3970,3973,3976,3978,3981,3984,3987,3989,3992,3995,3998,4001,4003,4006,
	4009,4012,4014,4017,4020,4023,4025,4028,4031,4034,4036,4039,4042,4045,4048,4050,4053,4056,4059,4061,4064,4067,4070,4073,4075,4078,4081,4084,4087,4089,4092,4095 };

#elif defined UPDATEABLE_LED_BRIGHTNESS_RES_10BIT

const uint16_t gammaCorrectionLookupTable[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,
	4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,6,
	6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,
	7,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,
	9,10,10,10,10,10,10,10,11,11,11,11,11,11,12,12,
	12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,
	15,15,15,15,15,15,16,16,16,16,16,17,17,17,17,17,
	18,18,18,18,18,19,19,19,19,20,20,20,20,20,21,21,
	21,21,22,22,22,22,23,23,23,23,24,24,24,24,25,25,
	25,25,26,26,26,26,27,27,27,27,28,28,28,29,29,29,
	29,30,30,30,31,31,31,31,32,32,32,33,33,33,34,34,
	34,35,35,35,35,36,36,36,37,37,37,38,38,38,39,39,
	40,40,40,41,41,41,42,42,42,43,43,43,44,44,45,45,
	45,46,46,46,47,47,48,48,48,49,49,50,50,50,51,51,
	52,52,52,53,53,54,54,55,55,55,56,56,57,57,58,58,
	58,59,59,60,60,61,61,62,62,63,63,63,64,64,65,65,
	66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,
	74,74,75,75,76,76,77,77,78,79,79,80,80,81,81,82,
	82,83,83,84,85,85,86,86,87,87,88,89,89,90,90,91,
	92,92,93,93,94,95,95,96,96,97,98,98,99,99,100,101,
	101,102,103,103,104,105,105,106,106,107,108,108,109,110,110,111,
	112,112,113,114,115,115,116,117,117,118,119,119,120,121,122,122,
	123,124,124,125,126,127,127,128,129,130,130,131,132,132,133,134,
	135,136,136,137,138,139,139,140,141,142,143,143,144,145,146,146,
	147,148,149,150,151,151,152,153,154,155,155,156,157,158,159,160,
	161,161,162,163,164,165,166,167,167,168,169,170,171,172,173,174,
	175,175,176,177,178,179,180,181,182,183,184,185,186,186,187,188,
	189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,
	205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,
	221,222,223,224,225,226,228,229,230,231,232,233,234,235,236,237,
	238,239,241,242,243,244,245,246,247,248,249,251,252,253,254,255,
	256,257,259,260,261,262,263,264,266,267,268,269,270,272,273,274,
	275,276,278,279,280,281,282,284,285,286,287,289,290,291,292,294,
	295,296,297,299,300,301,302,304,305,306,308,309,310,311,313,314,
	315,317,318,319,321,322,323,325,326,327,329,330,331,333,334,336,
	337,338,340,341,342,344,345,347,348,349,351,352,354,355,356,358,
	359,361,362,364,365,366,368,369,371,372,374,375,377,378,380,381,
	383,384,386,387,389,390,392,393,395,396,398,399,401,402,404,405,
	407,408,410,412,413,415,416,418,419,421,423,424,426,427,429,431,
	432,434,435,437,439,440,442,444,445,447,448,450,452,453,455,457,
	458,460,462,463,465,467,468,470,472,474,475,477,479,480,482,484,
	486,487,489,491,493,494,496,498,500,501,503,505,507,509,510,512,
	514,516,518,519,521,523,525,527,528,530,532,534,536,538,539,541,
	543,545,547,549,551,553,554,556,558,560,562,564,566,568,570,572,
	574,575,577,579,581,583,585,587,589,591,593,595,597,599,601,603,
	605,607,609,611,613,615,617,619,621,623,625,627,629,631,633,635,
	637,640,642,644,646,648,650,652,654,656,658,660,663,665,667,669,
	671,673,675,678,680,682,684,686,688,690,693,695,697,699,701,704,
	706,708,710,712,715,717,719,721,724,726,728,730,733,735,737,739,
	742,744,746,749,751,753,755,758,760,762,765,767,769,772,774,776,
	779,781,783,786,788,790,793,795,798,800,802,805,807,810,812,814,
	817,819,822,824,827,829,831,834,836,839,841,844,846,849,851,854,
	856,859,861,864,866,869,871,874,876,879,881,884,887,889,892,894,
	897,899,902,905,907,910,912,915,918,920,923,925,928,931,933,936,
	939,941,944,947,949,952,955,957,960,963,965,968,971,973,976,979,
	982,984,987,990,992,995,998,1001,1004,1006,1009,1012,1015,1017,1020,1023 };

#elif defined  UPDATEABLE_LED_BRIGHTNESS_RES_8BIT

//Lookup table for gamma correction.
const uint16_t gammaCorrectionLookupTable[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
	215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

#else //Default = 8 bit

//Lookup table for gamma correction.
const uint16_t gammaCorrectionLookupTable[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
	215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

#endif



#endif





#define DEBUG_LED //Comment out to disable debug to serial monitor.

#ifdef DEBUG_LED
#define DEBUG_PRINT_HEADER(...) {							\
									Serial.print(millis()); \
									Serial.print("::");		\
									Serial.print(getID()); \
									Serial.print("::");		\
								}
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__);
#define DEBUG_PRINT_F(...) Serial.print(__VA_ARGS__);
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__);
#define DEBUG_PRINTLN_F(...) Serial.println(__VA_ARGS__);
#else
#define DEBUG_PRINT_HEADER(...)     //now defines a blank line
#define DEBUG_PRINT(...)     //now defines a blank line
#define DEBUG_PRINT_F(...)     //now defines a blank line
#define DEBUG_PRINTLN(...)     //now defines a blank line
#define DEBUG_PRINTLN_F(...)     //now defines a blank line
#endif






//Gammacorrection achieves a more linear perception of the MultiLED when increasing or decreasing the brightness.
#define GAMMACORRECTION_ON		true			//Gammacorrection enabled
#define GAMMACORRECTION_OFF		false			//Gammacorrection disabled



class GammaCorrectedLED {

public:

	// Constructors

	GammaCorrectedLED(char* identificator,
		uint8_t ledPin,
		bool gammaCorrection = false,
		BRIGHTNESS_TYPE lowerLimit = BRIGHTNESS_TYPE_MIN,
		BRIGHTNESS_TYPE upperLimit = BRIGHTNESS_TYPE_MAX);

	// Setters:

	void setID(char* identificator);								// Sets the ID of the LED for logging purposes.
	void setPin(uint8_t ledPin);									// Sets the output pin to a new value.
	void setGammaCorrectionEnabled(bool state);						// Sets the gamma correction to on/off.
	void setLowPassFilterEnabled(bool state);						// Sets the state of the low pass filter.
	void setLowPassFilterSmoothing(float smoothing);				// Sets the smoothing factor of the low pass filter. Must be between 0 and 1.
	void setLowerLimit(BRIGHTNESS_TYPE lowerLimit);					// Sets the lower limit of the MultiLED.
	void setUpperLimit(BRIGHTNESS_TYPE upperLimit);					// Sets the upper limit of the MultiLED.
	void setUnscaledBrightness(BRIGHTNESS_TYPE brightness);			// Sets the brightness to a certain value.

	// Getters:

	BRIGHTNESS_TYPE getLowerLimit();								// Returns the lower limit.
	BRIGHTNESS_TYPE getUpperLimit();								// Returns the upper limit.
	BRIGHTNESS_TYPE getUnscaledBrightness();						// Returns the value of the current brightness.
	BRIGHTNESS_TYPE getLimitedBrightness();							// Returns the value of the current limited brightness.
	BRIGHTNESS_TYPE getGammaCorrectedBrightness();					// Returns the value of the current gamma corrected brightness.
	uint8_t			getPin();										// Returns the output pin number.
	bool			getGammaCorrectionEnabled();					// Returns the state of the gamma correction.
	bool			getLowPassFilterEnabled();						// Returns the state of the low pass filter.
	float			getLowPassFilterSmoothing();					// Returns the smoothing factor of the low pass filter.
	char *			getID();										// Returns the identificator of the led.
																	   
	bool			isShining();									// Indicates if the LED is either fully on or dimmed.
	bool			isMax();										// Indicates if the LED is at its high limit.
	bool			isMin();										// Indicates if the LED is at its low limit.
	bool			isEnabled();									// Indicates if the LED is enabled.
	bool			isDisabled();									// Indicates if the LED is disabled.

	// Methods:

	BRIGHTNESS_TYPE update();

	void increaseBrightness(BRIGHTNESS_TYPE amount);				// Increase the current brightness by the given amount.
	void decreaseBrightness(BRIGHTNESS_TYPE amount);				// Decrease the current brightness by the given amount.
																	   
	void enable();													// Enable the LED output.
	void disable();													// Disable the LED output.

private:

	// Fields

	char *			ID = "Led";
	uint8_t			pin;

	BRIGHTNESS_TYPE brightnessLowerLimit;
	BRIGHTNESS_TYPE brightnessUpperLimit;

	BRIGHTNESS_TYPE unscaledBrightness = 0;
	BRIGHTNESS_TYPE previousUnscaledBrightness = 0;

	float previousEndBrightness = 0;

	bool			gammaCorrectionEnabled;
	bool			lowPassFilterEnabled;

	float			lowPassFilterSmoothing;

	bool			enabled = true;
};





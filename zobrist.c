#include "zobrist.h"

const u64 zobrist_keys[] = {
	0x6c0e2d01f044146b, 0xf4325b80f9efa821, 0x24eafe3ce66bf326, 0x444dbbe428ba2eb6,
	0x1c6eb7dc19100464, 0x6ee3566d4b76a0bf, 0xf981b1ccb27e4b48, 0x6b394da27b5fc554,
	0xef3803cef221e17f, 0xac7695f96d95ff78, 0xd2bed95c22c1f5d5, 0x98f8758e6df79a07,
	0xf6b0184f550f3c54, 0xd816d6adb4baea6f, 0x84f30995061affd8, 0xe9cc22c99cbea49c,
	0x3e37b67906bfc1cd, 0x51e2287cd0131e2d, 0x6a9cafa715ee6640, 0xc89d16b922a6c5f6,
	0x8760161ca0d02c6c, 0x76b166a834d43fce, 0xe249815ba1a2e662, 0xeb927349b1440808,
	0xb5bb4713e9781b2c, 0x247a400c9d6b6e44, 0x6565cfbdf515d07b, 0xd21f97943fe7aac9,
	0xa95fbac4f71abf43, 0xd8b9ed5be2613677, 0x050d7df39931084b, 0xaa73d675b93f225b,
	0x879a2cf639c9fe0b, 0x11fe069729493bed, 0xf9bb54002b3cc908, 0x95a903c35a6fdb82,
	0xf706d9847df17786, 0x99c24d6c49a1284e, 0xf5776445c1e8d0c8, 0x6d11e2ae84229b7c,
	0x0732780e2da332de, 0x0e6c194f32958b48, 0xcaf6481fb270ee74, 0xe71ca5c66ad14a77,
	0x9224455fa3b9d2b1, 0x52db43423e33bb0b, 0x04b04c84671cf233, 0x700217c949a07fd6,
	0x8e1f4077d212b76b, 0xe1de439ead3b5cb3, 0x5814b89a9bfa2596, 0x3dd1d9b041faea40,
	0x2e8c32a20b92b06d, 0x1c6f63577b25ab0c, 0xa0c9f8575c0f3a0a, 0x6c2e79a0c56bb2d3,
	0x3c98b9ad9f5335b0, 0xb2f8af81abd3fc89, 0x8ad41305723a0e87, 0x9e101bb460894a6c,
	0x27fa6b2ad8031b0c, 0x5f8a29bc159b6690, 0x715361613f78191c, 0xf3b8968b293d0e5a,
	0x5680ff3ad86d7206, 0x5115cbbd114d32d4, 0xe71b4cf1d7875622, 0xfb1a04e54f589a37,
	0xd582e39868160ec9, 0x492fef245e97bd40, 0x686fb8c2f9b0ad51, 0x817edcece5c44816,
	0x2e83dae9fc683102, 0x1a728e9304aba9ea, 0x8bd81ab51765cb91, 0x23c9b19929355fd2,
	0xd2762f273d506fb7, 0x7fe642f9ff9e1124, 0x7f6fb31b17397d3f, 0x9d0643800ea15319,
	0xed42072b8b0d4a8a, 0x4bd5b7aaf1169809, 0xfc90c5df0846b4c3, 0x32ea03d23220ecd1,
	0x64c30299b1d38ced, 0x6cb2b06e41355e8d, 0x4337668ab9691f89, 0xb027b3280932f08d,
	0x8dba53c4b396e578, 0xa4990ec94a2085d7, 0xbbe63ebac8afe895, 0x62198f38ff7b6d64,
	0x1f10337e9fc85544, 0xa90e1aa4a9eea29a, 0xbc12f85cb80405c3, 0x99389dfa4476f76f,
	0xd49a779806d8bf6e, 0xc5d99179c28bc18a, 0xa40a83a74cbe375a, 0x0d68b0d9adfc0e3e,
	0xfb4c11558beb413b, 0xdf1fd2f9ac946d06, 0xd50a87b1939ba05f, 0x8660f8521d7eaf51,
	0x648a0fba59ec08f8, 0xfeac50f009b396ab, 0xc1cd22a7e1fcadfa, 0x070c3d286b1c7f83,
	0xdf513d629b4ef8c8, 0xc27306a0147fca0d, 0x951d582fce9e106b, 0x3afedd1ad0ccb40f,
	0xe1a89b4d1f569e06, 0xbb3927e5b136f964, 0x64029eb7a7f2d516, 0x0acf124cabe7a506,
	0xc6ac5809841dfaf7, 0x7dfb9e342e5a4e0d, 0x2ea6e84a61aff474, 0x641f107ba3d0b315,
	0x9fd6f39354789386, 0x942a93b251ab6e99, 0xc2aa59d40ce9315b, 0xaf5e6e8d7873181e,
	0x618019803f298e06, 0xc0f9d646a3f68e86, 0x4a9ccdbf612eda19, 0x50b7258004eb325f,
	0x30449e09dddac3f0, 0xf7c9f3952f4641c2, 0x8d40791435fa9ee2, 0x8c9b47df5abbf43e,
	0x74c0166c1e3aafe0, 0xa23601a7617d998f, 0x5927cd2ef7ceb5e8, 0xb634eeb78a56fe1e,
	0x599810768fee8fbf, 0xa14ed4e916d0e353, 0xc1043aa14ab3c9d5, 0xb2ab0552cbbcc616,
	0xac0ce473cb1d5f91, 0x937eaa6eed68c4ce, 0x6353780a04584bcd, 0xabf8efe850f103fc,
	0x7578a6d3b5fa096d, 0x82b2cb19e2c209f3, 0xdf08f953c226a4e3, 0xbe5d30e9bb88f295,
	0x3bbde9b313cad3b1, 0x5c6c33d03b6d6600, 0xfba644d30e1cb2c1, 0x63de7126f8b5a7ff,
	0xd05355820bc06bad, 0x0febb540b585a60b, 0xad0489377b4cb0bd, 0x3de8516a2e159932,
	0x4eb48e9fb364d777, 0x8c0ee7001e1c36d6, 0xa625aa9fc82f8757, 0xb629308e46a74338,
	0x702e74383b746c61, 0xa9272350b7e65de2, 0xeaffdb530fd1e5eb, 0xf298d689be9824f8,
	0x1a48fb37828db5d0, 0xb88f15253ab4f22c, 0x78b90a85c78d99f9, 0x87eb188c75b48a03,
	0x2bcc3a38b3811f37, 0x79f3c63e20b17cf9, 0x6a76b7f5d410cf24, 0xcd791d777a983739,
	0x522d974aae37fca0, 0x61aab026fe0fe829, 0xe375e1727b523c12, 0x88ab757f3b2df7cd,
	0x2bd066117c5d8749, 0xe1a6d54ba1c90adf, 0x6bef4a6a58af40b4, 0x7de9387fef85085d,
	0xf212bdbd339a6d0c, 0xdf3178e6716fa8e7, 0x2ef97cf465ede14e, 0x477c8141eb4dd0ba,
	0x2e76bc320433590c, 0x1d0e009ea590eae8, 0x95d98ff32c106d88, 0x528b8bdf7d64b8a0,
	0x624814ae854a517f, 0xd4a27683c0db8f42, 0xbd01372d72e0d3e4, 0x188ead6b2d9b1829,
	0x35e880afcb3d9d33, 0xcc235a40a556c99b, 0x368dbb4b29e0faab, 0x441967cdb428c414,
	0x940bb29fc0b02186, 0x1a9aac0be9be105e, 0x17e059836da7390d, 0xc416234ebbf0d6c1,
	0x21278654b98ecbf7, 0x55402963768e49bc, 0x7111821ea24a2ab4, 0x3333917764fd4bb2,
	0x19ebc0f475004c2f, 0x79ba57f1513f31cd, 0xb006dee80e758df5, 0xb9aedc1daebc6bf7,
	0xf59b6625ebeae911, 0xd2e6cafe72d8e860, 0xf854c86d962a1d60, 0x39613151315d4c6b,
	0x0fe7990f1c618274, 0x40e616c9d092bd5b, 0xe7426849d47e13f5, 0x04008944e7f20325,
	0xcbb443efb9f13acf, 0x5376a5d1f6b44d5a, 0xb0fc1cc415c1155a, 0x57da86eae085dfbb,
	0x43fa2e8c36cb9196, 0xf809bf099dfb37bf, 0x9398e623f79a29e1, 0x425d07bee4b89e3b,
	0xa723538873101bbf, 0x8526478df91b4c13, 0xec4be121dcb0055e, 0x2ae163bf08a941dd,
	0x985c27d61adac765, 0x08f20ac8fc8110be, 0x795d57e1021a46e6, 0x3c687ac17c82a785,
	0xfb28f448aa758215, 0x1fbf98c08d18420f, 0xdf34abe221f72908, 0x5fe4a2a681fabfea,
	0x3a6ed02f02c56d59, 0x8044995e793b2e5b, 0xb53f68353d9a0be7, 0x2c09a01c9a9db7e2,
	0xe1d53ff701d07917, 0x991fbdf871e6df6b, 0x29ce1c2753d983a3, 0xce2fa982d09679b9,
	0xf8439382cd7ad74c, 0xdc640175aa8755c6, 0x2208276a14bdd0e3, 0x5b629b9b29f13083,
	0x7f94c9eb5eec3fe9, 0xdd1cd712e04f5f9d, 0x4c34403a13161b08, 0x9c0533206172babc,
	0x706d7fe865f8f739, 0x0641b66a9b7498a4, 0x54fd81f2f8677440, 0x4c73d0fd826c7003,
	0x97f6dccd8674f65c, 0x475839bc36ab0b24, 0x5225252df1f9e3d5, 0xd7746dbdd8e043b4,
	0xc2fe282e74c04f00, 0x4ead532f70957d64, 0x8669d09d4b9115b4, 0x985e9dc1f0bb55cc,
	0xeed10dbd58666199, 0x82a9dfd47cbf1d5c, 0x110afabad6902c4c, 0x4cf2e90376a3c29e,
	0x220da4ad9e8b55cf, 0x475148eb1041b60e, 0x4503e6413be79865, 0x5a8b69e43e0317f0,
	0xb2bf06e71b733585, 0x4e2e14b127bf2c82, 0x14b4381b005eac08, 0x8aa7e0dd02ccac8e,
	0x3a593c07ab669340, 0x57e70714a4726e16, 0x34af82c9de7e22f5, 0x9142dd8976158ed0,
	0xbfbc4a93e6517d39, 0x52209afd66132236, 0x740dc8f60290f439, 0x12a7c69eccec6475,
	0x55f28456b8309c5f, 0x2c9a246f26aef489, 0xdf4a94f24c32e155, 0xb2c66d6844210048,
	0xd310050dd0dbc6da, 0xeb34f4d3b80a0b40, 0xd39ee5fed828babc, 0xb77e1eb88ca017e2,
	0x777fbd8c52b34db9, 0xb32aeede0704b945, 0xa8c621034a421dc6, 0x93da0a45e2691b46,
	0x46c5b0c41d5eafeb, 0x9fa6bb382d3a11ae, 0x18b8af3b591607b7, 0xf8640c4099b81917,
	0xced5fea9f79247a3, 0x3397b619b0b46361, 0xc44b96a3f27948e9, 0x37f2020416f95b90,
	0x47e8ed1aeffa826d, 0xbff34d26629564ec, 0x86d8065c734a4bac, 0x0b11a1517e9288a3,
	0xd128f3932d736848, 0x693d73d8d7586caf, 0x016d144773e313ad, 0xa75f2a156a5b349d,
	0x1dba33c72705b9a9, 0xc39599bf17bc9976, 0x379d7b48d9684e1c, 0x1fd5ef1c8fd6d117,
	0x41ad40d4de371d8d, 0x7e0927d7f0688295, 0x3fcf93667152887a, 0x0d13c3ba323bfef1,
	0xb9f8c055191544fa, 0x307903935e045678, 0xe4ae80a8be2b6255, 0xa45cc0b55cb5a582,
	0x094c1098680690f0, 0x807b4a98e9e3ddeb, 0x761ac160a85e3de5, 0xf0c8669f7575cde7,
	0x9bb9d0ff96b8591c, 0xaafa1a730aacbe61, 0xc671fbe579570540, 0xd0877b842c856d66,
	0xf133fffbba8c2536, 0x7d785138b675340b, 0xc4c0999b57a48850, 0x23de877370c9ffaa,
	0xc65beb220fecf3b4, 0x587b9c7274de145f, 0x1bb7751107a91f2e, 0xd17df2aebe677e3b,
	0x00968d837517188c, 0xb46899a810fd8940, 0x22ea5394e20a32ce, 0xb813de2a1f1643fc,
	0x39e970d3890d488b, 0xbad9e992aeb0e5e4, 0xfbcdc990ef9ed771, 0xd3f600153b13b451,
	0xa032ab7675324d33, 0x17ddca9012c92bd4, 0x4434bffc0c058810, 0x1f3bed1165e7e923,
	0xae90e4133e58cd24, 0xc1dd2d0a558988a1, 0x95681d362a8d28f7, 0x598da2bf44ef269e,
	0xda5ab63eef24b75b, 0xbf1fd30b3aac4047, 0x8b3ceb88106236f8, 0x8d838c30214af209,
	0x7ab4c41a70566d5e, 0x3a6c6a724cd6b79f, 0xbb8d40f419029aa1, 0x8adad9d41dcc4f30,
	0xce70bada559a5c95, 0xb9ef52c20dcb28df, 0x3dd885ea10d3796c, 0xf083ac20996c0c8c,
	0xe7801db774ad2791, 0x5ea21ca93c360c36, 0xa72af441d2518cfa, 0x0ff54b308b8e3032,
	0x2cdbef508f98c7bf, 0x9f5b1949b76493ba, 0x2f923a869ad8e068, 0x69f755ffc6bea278,
	0x2af35aee12cb3c6d, 0x1090d48b38dbf64f, 0x553c3d82bcaabfa7, 0x94dd2ed19ee13fa8,
	0x515e843eea287684, 0xac071aa73d8446a9, 0xcc880a96c46e72b0, 0xda1ee6280d72de05,
	0xd5d4537f2f1c9b43, 0xa64fd8c26d7bdcbf, 0x638ec7c128dd15df, 0xa5f65f47202de44f,
	0x79213e770a2bf314, 0xcac0c72f870821af, 0x4006097dc0369389, 0xefede744441a5015,
	0xd1706e41ee059d14, 0x1c42e7c0547b1c9f, 0x74c165b6716657ad, 0x37d7c8456d01f611,
	0xc2a0b04f478e26b2, 0xc263fad01f884e5f, 0xb1d7d65bcd3cb493, 0x1dcfa0131044f76b,
	0xdf20d334688df26e, 0x4e0156e2c4f8f8b0, 0xb0177ccccaade40c, 0x16653a875c145f85,
	0xe95d8bb9903d9704, 0x3eb6f5e088e10cbf, 0x5100f232786f4ef9, 0x53921ce18f4e311a,
	0xdd45b913eec06857, 0xa23a450a09999a8b, 0x71b16e249498fab4, 0x11c70986b25ed667,
	0xd4980fc1644cc826, 0x770344fffbdeec6c, 0x3308c6d18354305d, 0x5a6da4d864f4d368,
	0x51149e1d92b5d551, 0x6755968ef9220f22, 0x90dd4f58a5916d15, 0x8110a0c867b877fe,
	0x499d430f053dc3f1, 0xfb171a5c3535c1e4, 0xc0e03dd33c97e881, 0x082c121a82090109,
	0x3f3e6872ca2e6a88, 0x2a63b8d8e13b5332, 0x1e0133a9f7ec6ec4, 0xc6424e6f58fe2e2a,
	0xd4dc65500416d26d, 0xfd492de759747961, 0x7ccd99d3f113734e, 0x390d77965e61caa8,
	0xc78995b99423874a, 0xebbc175b5c3ad3d2, 0xfab19698d6edb2eb, 0x62b4ab1ee847d263,
	0x5f576456468632e2, 0xec3d899601cbe8a3, 0x2ed64b60fee785d3, 0xd24871c8b3d658dc,
	0xb07a9e62b432c2dd, 0xe60038f57c7de57d, 0x2557071c528096c5, 0xc40d6b21e3579277,
	0x1fbba5c751e3207e, 0x1105105694ce83e2, 0x8c9778ffedcad071, 0x61f299c3162f4d9c,
	0x2c45dec4d02e190a, 0x0f9149f5be8d2b0c, 0xf9c06fbb4eda0470, 0x67dc8c97015d145f,
	0x6acc11300200dc1f, 0xadb187c9e0ccf76e, 0xcedf0b0f65b70941, 0x23d3e287419fc4d6,
	0x9dfe02f13426cdb5, 0x942aeb418bb30e86, 0x0e9af0c6febd0e35, 0xfdee028dc5644b58,
	0xcf1975d93cd91c8e, 0x971d396d51002693, 0x1a7d7dc5bbe1d5a5, 0xdf86ab26b420e6b7,
	0xd6075160d0136c48, 0x20c865e8e06a6c9b, 0x6e75ce3c3ae734b4, 0xc48b39ef439a4a54,
	0xe873a58497e5e192, 0xb6bfd3d7dda65c55, 0x79ff0110c5b58763, 0x5086ca80209ae757,
	0x601f0f4067f9ab9f, 0xbf1ab8d2648117be, 0xa26642cd601364db, 0xa74a78cf1544a8a1,
	0xb6cf5653ce6f1d30, 0xd9f1b76cb1a0ef75, 0xb2ac66b99cc2535f, 0x851af63bbc705a03,
	0xd56338cb803f4be2, 0xe6c50fd69cce3720, 0x4dfece6511541d53, 0x3f09c383afc5cec9,
	0xe8f0d2e6dd2a5842, 0x645b46e0d941fab4, 0x44e1d39ed6e64c0f, 0x600f3f1843fc2a0a,
	0xb988226accc1bbc3, 0x3118a4bd9838dd53, 0xe75af5331dc85fae, 0x26541e6f47122eb0,
	0xceb13538b8929f3c, 0x69b8a5001f19c83d, 0x56ed0cd92495f867, 0xbec8f3fb96b18166,
	0x6ad4500e753c62f6, 0xebe8f026cc4bf5e4, 0xa4f1bab75b1ff733, 0xecf86fececcc7cf2,
	0x37066d609ba820fb, 0xdb253314e708aaef, 0xa528446fa9afcbb5, 0x5de9ba9f9c58c783,
	0xfdf29e4b46c2b6c8, 0xb8cb5bae461d3b3f, 0xfa66cc430f880ce2, 0xafb591108b69787f,
	0x44426dac31a861d4, 0x8c11e845aa5c82c3, 0x4eee7b9be6dc3a98, 0xc110311de86a69fa,
	0xad80a6e1e1d3a3b9, 0x613b907c825f228e, 0x07a574dc850ed896, 0x4c6fc1c5bd1f561a,
	0xe349bf96d4d6bd5c, 0x2fc1cbb4f2bc8878, 0x4e995381375b8bee, 0x73f323a2bce9d3e5,
	0x46bd21b12f7b70ab, 0xbf7da5e273bb1b33, 0x3ed9771a90c6f72a, 0x3a516f767b07c5ee,
	0x108bdeb597c6451b, 0x39bf497a48b118f2, 0xe9a2cfe07b524a5c, 0x3d4e216caeff67dd,
	0xa54f673bb06f5fa0, 0x0e154fb1dfc89b30, 0xf51af8ab350b6106, 0x362e5ae2ca07687c,
	0x91bd3bfc89656147, 0x420176955b0a4ce4, 0x07100ee2670cff1b, 0x2d94147421b0fb9a,
	0xeb99b91f97ea535e, 0xc16731e0ca0b37a1, 0x6a80aa50aa24cc15, 0x81d75708ab48b296,
	0x1d5a42db3aaa161e, 0x0873022248fcbc4d, 0xd10b78b03b7a02a1, 0x5775cd1263cc7e74,
	0xcbca81370f07120d, 0xdf0f049e2af41892, 0x9dd1e96e4d3771e8, 0xc7b47d962bfccf2f,
	0xc8075d38dcf10828, 0x4af23502414c3287, 0x62a2c2e6dc0ef76b, 0x6c594d9ee3e2bd28,
	0xd7a8e600d3c941ad, 0xd5363c1254104031, 0xece6250eb9494ca8, 0x1562052a595d307a,
	0xeaf9eba21d3009c4, 0x0c8af048399f8e52, 0x459d5fde91b73978, 0x755721dd096a14c0,
	0x0e6d825b8384979b, 0xddc1ba6f3232fac4, 0x3ce3ec04e615d077, 0xd91a6537754d6a58,
	0x76deec705e0984bc, 0xf3ba9645dc6ce298, 0xda1d438cea60f645, 0x516dc9e9de567042,
	0x7826d98606444ec2, 0x2b681c15d296bc09, 0x2de160db6911b523, 0x801c4629b8d496f7,
	0xabca0da09ae29e83, 0x18de173258f2df2e, 0x1637c7a1463f50e1, 0x48b5a253e3929c1b,
	0x998bf6595a4b3477, 0x2d90a0476ad25cd3, 0x66d803d6b28c3208, 0xc3417457e0fd4714,
	0x88a3eaedd28791cb, 0x7c1eaf8803d168ed, 0xa9f59ac0f7a15b37, 0x20f0ce696a649a4a,
	0xd8aa8b357307ef2d, 0x66949fe2b1fe5fa6, 0x8db096745534928c, 0x19e4af1d37a214ad,
	0xf301344e8ca921e2, 0x8ca2f5c554ff3475, 0x7070fde10a379b86, 0x70b9d10afdd8b9bf,
	0xb5c246d65508f5ab, 0x76711ebb21548bb7, 0x0713e58ff7f0b707, 0xc332e4792924de11,
	0xda8ccd9e8d1cdbd6, 0x9ecdd63f5d588c8b, 0x744650422da0c60f, 0xe36d4bbba229a101,
	0x41913e52df8af318, 0x51b06b66d59f2f7f, 0xae8f8104548bfb94, 0x847e6d0a8b6ac714,
	0x41efcbe78f2a7621, 0xa599f476993fa9b5, 0x810cdc753a4d1d28, 0x89ea21ebfdb1fe4f,
	0xfa0f0b9cbff28180, 0x8284d554095fbaaa, 0x5c407deb878388e7, 0x1408d4d8a3e573dc,
	0x62797d4c9759e7fb, 0x496309e2e161673f, 0x24c6b651c6aa8c7d, 0x3d464e4f6fa23824,
	0x289a42082dd484a1, 0x3ba5f44722e99264, 0xd2fd00eced8967f3, 0x1bba20bc20bdeb15,
	0xe121ab09b4b55efe, 0xac97fd011decf2c9, 0xb5a40476faa21b68, 0x69be6a6bb608a7f4,
	0xedc90ca13ddee953, 0x229f1503bc4ed2c2, 0x0b52ac2162082d97, 0x50ee5d57fcff1b1a,
	0x26721bc870d0e583, 0xcf7a12eb933d2194, 0x5c67f91a17fe6cb2, 0x2eb91b2c9f9cd83d,
	0xa9fae91242f9f9cb, 0xcf905c0a5e78c9c1, 0xe99fa23e87b34702, 0x0573c649259ba65e,
	0xf36fc520e5c989ae, 0x104cd025c8dd4b42, 0x84ef0ce1a7fd7443, 0x7d4cd1370fa7f82b,
	0xe7c550d1ca542efa, 0xcc698b59ad65dc95, 0xd1aa236b2beca4f8, 0xe68ecfa79764e997,
	0x5c418c232d7beba9, 0x3b3fc7fe6e8111d2, 0xb3970776064ec431, 0x0dac08384946ff64,
	0x3030bf4fab01ccf6, 0x9019d8da629ac6b1, 0xb675e0392cb51826, 0x7d2ea45686f2a249,
	0xda07a7d96406f62f, 0x8ecc4bcb56207a84, 0x51b0f74938450bf0, 0xf2e01ec9335f380a,
	0x90d19689b114ea45, 0xcdcbb2118d2a1920, 0xcbaaa589c7156b4f, 0x87b86c5a1570b539,
	0x7828adb8b4c8f49d, 0x42b1642593ea6284, 0xdd6a5e570a1550aa, 0xd7465222587b643e,
	0x6f3fa112659f78c4, 0xee972594fe1f510c, 0x9cb434c3d1465f40, 0x56cdfd9300c3b3e4,
	0xb4486126d19c0646, 0x0b432303118ef3d7, 0x1153f6747fb695d4, 0x49384040954e6061,
	0xfe0ca468194121ab, 0x77a9b7f1af7862c7, 0x0aabe2205586c029, 0xa01624dbcece84e5,
	0x1a02f935818c0480, 0x95da21d3f4930846, 0x093cee5f675af98b, 0xb67093f41fba8147,
	0xa5e22274e8a79500, 0x3e27a76db51a11e9, 0x07945106d13a5095, 0xf77348d93135e3f8,
	0xc74f31e284fd0668, 0xeb6a80fa2ea2a286, 0x83a125f634645626, 0xe9056b32412a67c7,
	0x28d5af46521464e8, 0x4c35976eb70401c4, 0x3b43739d7a39f398, 0x5f0e7c08efacf430,
	0xe5565f117c6ff8fd, 0x3dcc4557c8299938, 0xfbbfafb23147bc69, 0xa0900f7e94acd05f,
	0x2b1fe9d92616d077, 0x7a37ee44c8f144ef, 0xffb88f36ed6b7450, 0xbe79d0aa67cfd909,
	0xb8c461978a414011, 0xa12129de4a8145e9, 0x1a8a6eb4fde57ada, 0x2b07367027e61561,
	0x2d01c443444a51de, 0xd33040a662aa176e, 0xf3daf0d59697e002, 0x4dc4685c708f7cae,
	0x9f72183d285a5dc1, 0x3ce2202a28780423, 0xc7ff8bfcd87fa3d4, 0xfe4be1cdc26aefd1,
	0xc924d06f3c510f3d, 0xba628512304e56e7, 0x597ea585425e35d7, 0x509954eda05e557b,
	0xdf6e7fdce081038d, 0x310e5d555329ae9b, 0x6b941df04c80c4f3, 0x477928145e82ce5c,
	0x3e7341e48471f4a7, 0x29340e53f6bfb932, 0xa9f8a986150085fb, 0xa474510046be7ad1,
	0xbd18b93bc9796c73, 0x9d653f783a48ce62, 0xd8f257e69f1ad5d0, 0x90f3d9c1ade7bbc7,
	0x183b14d3b6d05af9, 0xcb401ea0a552762d, 0x9330467ddfae3a37, 0xf181bfca1110af79,
	0x14948175d391ba84, 0x546cd6c2aeb5510c, 0x5f22f1bf6a0b2d4d, 0x03ddb45fc9a5ccf7,
	0xfadd47248492cfa1, 0x66e5fbe1dd401264, 0x4579dec0e5528ecb, 0xf6d04a6260e854b8,
	0xf4dbd32b1c3ded3b, 0x5031df4722a7714a, 0x642a1cbf2ce33fe3, 0x6d130278be39d965,
	0x6d8fdbd529fdf55f, 0x323e20428e478805, 0x226d4337ac1b4907, 0x33227310e1129131,
	0x9351f1c0358090e3, 0x4ffd5f2657da6658, 0x099d57b48b1d23c3, 0x3772d6488749f20b,
	0x8d59df00772d45e5, 0xfbb199e64471e736, 0x65a95c426a2c50fc, 0xae27bbd28d728c8b,
	0xf9e350c99d2bd0dc, 0x243cce368cc8dc43, 0x3d04a7c98c0e0c7b, 0xca02520d5f75989a,
	0xa1937cb28c32fad8, 0x055d43a1856a2bae, 0xaf28088e87bbfa36, 0x682350059958a9f2,
	0xb5493515a6b99afc, 0x06e257d974801f61, 0xd55cb3c0c65e1df0, 0x41c935a2644cdef8,
	0x0cd0875869a7e43a, 0x6976b2aeef55a940, 0x33cbfae01680831f, 0xe98e1a908997a9ad,
	0xbb4518216e624945, 0x1ff774945ee3c69b, 0xb97c04ac71b00ab8, 0x59c57d1e00477dfd,
	0x5bd81c7f7eadba19, 0xd55ef4a9e83f8f08, 0xaecfbdb58faa3902, 0xe3cff88b95014d3a,
	0x0475a144df58bb22, 0xbd1a278aad8f5f7e, 0x0e842cb06b215f37, 0xc807da15ddd28239,
	0xaef8b95572dbf4c0, 0x8f0a77ed841db85e, 0x8734dccc250aa123, 0xb5b0738950eb466c,
	0xbc9e3957814aca31, 0x4c590c47d63cf8ab, 0x4c20ca33a97f16a0, 0x3c5f87ec8eb1d3cc,
	0x458458114a5ebcac, 0xed4fd6d0021e9f3b, 0x13b66ff1fd9f3dde, 0x9982dac084978827,
	0x18061338a8a03101, 0x8390157a5e69e2ad, 0x1ee36570b4ce2e4c, 0xa59bb9f3ca688ddc,
	0xd860895c8536b1db, 0x0a19a04cbfe72439, 0x7632b2df187de5a1, 0x6f0421b0cf2fc93d,
	0x3207da20ab8950ac, 0x035615dd7d0ed031, 0x7f92622f9aa7af6d, 0x8898a4c4df850009,
	0x439cd48d755b8bbf, 0xe18887e03ca48ab5, 0xeec25cb076d9b2de, 0xfa277abb88bd1e1c,
	0x25c22ff65cc1b0a8, 0x53a85a7d03d37207, 0x9652fe1c1ac708d3, 0x162365801da83a61,
	0x8df30dd62f0a02cc, 0x024dab325a79c123, 0xffb34fc68273e33c, 0x47e25cd9e355592e,
	0xae9e0d9d90345b6c, 0x27bd3acdf744ab60, 0xa919ac9803276421, 0x72605c9733529790,
	0x4bc47f24613d92f8, 0x8d9a7f120817e198, 0x8f11e03067a84d79, 0x2a6378a7a8a90861,
	0x4679c3da8130c4a4, 0x6b1ed931117dd8f0, 0xbeaca34199dec329, 0xcff78f20a98ab2e2,
	0xa5097ea99d81bb84, 0xe9eecbf98c5845da, 0xec2017f3362d0b7f, 0x597c58f50f694abe,
	0xf899e4ee23d0e05f, 0xbb4b4fd1e5b5171f, 0xb3dc7af6d412f2ad, 0x3dc79e3756d8e6ba,
	0xb41d1b9920175312, 0xc9c9f5b7d736bee5, 0x8253a889364e4d25, 0x79e20a7d633d90a3,
	0xc9f1cb62ce68a122, 0x461c125e8eab5854, 0x611f092b3b22fef0, 0xb40f91a77ed791b3,
	0x4d0b7a9cd352ec19, 0x500eb44050bf613d, 0x34e1484007e7eb15, 0xc44a5229b7e42f59,
	0x9d489648c3478a4e, 0x025a2d1dfb1325c0, 0xf53846843db0f8e2, 0xb674493247f5a6f1,
	0xa2f129eca41f0b84, 0x49d756e4246f5b93, 0x301ce56a11d14dcf, 0xc4cf81eeea2aa098,
	0x8013ba71f4358fe4, 0x11e2826d96812544, 0x8144d8e37040e4ae, 0x0f61b4f33aa8f533,
	0x1bfd567228ed3cab, 0x5c0d060fd805ae67, 0x87503c7e511340ed, 0xd9aa6af5ef674d39,
	0x5b536de4ac54644f, 0xd1d6f97b05032a08, 0x6f5602ae4c5868a4, 0x159e123cfdb1fba4,
	0xe7c068b754928813, 0xbd40daf77bf43ee3, 0x3acdd1e0bd907b28, 0x591c63775e02a4d2,
	0x220aac245fc0796d, 0xb834b0f08e02efc2, 0x8cac0c0386a8a521, 0xcce1c77496d36f78,
	0x1703f09890606345, 0x0df0681ad7a0038c, 0xae7a5272a970b631, 0xd0192d4c135e2200,
	0xc09ba5391b528294, 0x12d93edf3babad68, 0x7fd9a35e93379602, 0x27f91a98f46b81c7,
	0x47032bd7e71eff1b, 0x176aaaf4a73e3fea, 0x30eddaa1c1ad9769, 0x9c364df9d6f938d6,
	0xd24d7f087acaff1f, 0xea23d6991b5ecb8e, 0x2cd0781a9761a4f6, 0x3071dd50bad226d2,
	0xfb6a6f4405146934, 0x3ea47cfec6a0e385, 0x0b388f653b237206, 0x29ba6dd9a0199953,
	0x28b5d72afd899849, 0x7837ed7895ecdfaf, 0x4c7459db3e2681f0, 0x60ab84ebe387b248,
	0xfc5e9aa2c00c18d9, 0x0016487003fc5269, 0x53638b8b45039540, 0xf93b715d6a395056,
	0x2b01ad112b0c863f, 0x388676c0abc974ca, 0xcb09af53c31d5d09, 0x0b03436ef5de5406,
	0xf0e636277d6b687a, 0x21cf81d94fe08ceb, 0xa6c7924b768dfbe6, 0x33da0d7f1bbb0366,
	0x6927124b2f388fea, 0x8adf0ee3cf3e038f, 0x4bb5cd2238df9014, 0xf9baa4722c04d1d8,
	0x17df52ca7b2ba012, 0x0b80eda83dfd66db, 0x1f0eafe7771d3217, 0x56149720ca29e7a6,
	0x8853b737199d0100, 0x782081be811498f8, 0x2ba0bc42259e763b, 0xd657b26c750ac838,
	0x844e3a2b73ff1eb8, 0x3a38f3ffb77d140a, 0x88487ff9188023a1, 0x56d67e7c13a518c1,
	0x342a982ec47fc355, 0x5af06b1e0e2ee690, 0xdb087e6821b74e91, 0x7b86bf4a9af2c1a0,
	0x0ed391b08b971485, 0x38d59a2d7e01b2c8, 0xc533f3e383023849, 0xa7ef24fe4d24ae46,
	0x57d5b3733f435778, 0x66cbec9ad76e163c, 0xe7419fe5a04253e7, 0x72a316d485a46236,
	0x5038066dd26c5c91, 0xf9421b21bccfc7e8, 0xa995e79c398c8527, 0x2e82e4f2caf00c4d,
	0x29326c58154d776d, 0xd84f4ec281653c97, 0x7f691bb596e7c9ef, 0xf08442e9e91531be,
	0x31901bec8a40fac9, 0xa062a52ed41e2b14, 0x03c60b7dfac62cdd, 0x2afc207ad355ada8,
	0xe328c3d0e15a4e7b, 0x43268be5257a02f1, 0x30b32c8f79adffcb, 0x0ecd799451cb9a13,
	0xbd4073435b90ce56, 0x4fa8f534502beb24, 0x3f5024afb30ee6f3, 0x5061cf82560a1d31,
	0xd8928c9f5f209007, 0xfc53a58f0e8c4746, 0xa99a088072eb72b8, 0x9d8d4ac9fd5b30ea,
	0x6a4bfafd5cb32e94, 0xcfa9924b72e6b003, 0xe1485bf8eedb3827, 0xd22df4c8c4247c35,
	0x452ecc9a1121b8f5, 0x544929e856c7377c, 0x232e399358cbbbb9, 0xebd3474deb04c8bd,
	0x93c807c42542cc1a, 0xc8b61283e6d4131c, 0x3b4c6673590afecc, 0xb4a2044bba4ed5dc,
	0x8cc773f4f95dedc9, 0x40c53ea26819142f, 0xe330221d755fadca, 0x78830c680ef58f97,
	0xbdca78beadf839be, 0x44cc8eb4b670b938, 0xd39c1eed372634f5, 0x02ae2214f1be8e1f,
	0xe4c7a77e7de3b5f3, 0xc8800dc818e67f66, 0x25ec0df70b2466a1, 0x0166632ebabd25f8,
	0x21deb46956440320, 0xc1398ed050e94ab4, 0x362ca9addba280b1, 0x7a31b0216646503d,
	0x5b0b92a4847ff3d7, 0x1645c313e1bc3496, 0xc23c35555a112535, 0xd6958a21cf1a6d13,
	0x37caaf8ba25c2748, 0xed839b983c3b7f93, 0xdf491aa2bbe4c4fe, 0x59fb901bacb2af06,
	0x25554d5d540a2e91, 0x91a113a33ed855d5, 0xb36f82a52041ab22, 0x9db34d34d6596350,
	0x759afb77c854b952, 0x98d37d6e5b78dc3e, 0xdb6640603b833979, 0x2fd1987d9a3df5ef,
	0x751eabeb872f5628, 0xdb788f911f5c31cf, 0xfa786814f041dda2, 0x491d3adecd0d34b2,
	0xb76f73d75e71cb59, 0x055cc38067a69e02, 0x7cc04ff7a67ad8cd, 0x20f400f6fdabcd55,
	0x0f99080b6194ba43, 0x67f61c0365a72636, 0x0a99f2b07d0d751c, 0xbd6b67ff62c4986f
};
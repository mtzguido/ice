#ifndef __ZOBRIST_H__
#define __ZOBRIST_H__

#include <stdint.h>

static const uint32_t zobrist_keys[];

static inline uint32_t ZOBR_PIECE(int piece, int r, int c) {
	return zobrist_keys[r*8*13 + c*13 + piece + 6];
}

static inline uint32_t ZOBR_BLACK() {
	return zobrist_keys[832];
}

static inline uint32_t ZOBR_CASTLE_K(int who) {
	return zobrist_keys[833 + who];
}

static inline uint32_t ZOBR_CASTLE_Q(int who) {
	return zobrist_keys[835 + who];
}

static inline uint32_t ZOBR_EP(int c) {
	if (c == -1)
		return 0;

	return zobrist_keys[837 + c];
}

static const uint32_t zobrist_keys[] = {
	0x3bbe9c10, 0xed76f637, 0x3df1d5d9, 0x1444a83e, 0x2269d648, 0xfbcd455f, 0xd725b2a2, 0x3bf7dc1a,
	0x41b9163e, 0xb05c034b, 0x56c8c02c, 0x90f89a4a, 0x4d23b890, 0x78281fca, 0xd5761fd3, 0xe9674a56,
	0xa3648db6, 0xed36c5e3, 0x15857142, 0x2e1c935d, 0xb12c03eb, 0x05471050, 0x29118ea2, 0x5a5c23e0,
	0xc71fe2e6, 0x4c83c2ca, 0x9640a86f, 0x8310eebd, 0xfa5b0dfd, 0xdd6ff6cf, 0xcd61c519, 0xcd5ddca8,
	0x496c239a, 0x223a1290, 0x0ee923d1, 0xf4b9bb66, 0x7eba2404, 0x42c490bc, 0xe9e0924a, 0x5d11eda1,
	0xdfda098c, 0xfd8c6d8d, 0xcfbd87a5, 0x6c7137e1, 0x37f33ccf, 0xb791bced, 0xb2f0a53a, 0x8c367a89,
	0x308e1908, 0x222db2f8, 0xd03b5b8d, 0x9abbc915, 0x123e062a, 0xb8fef972, 0x048c4bab, 0x62a9d1a0,
	0x9a45bb51, 0x2903a24e, 0x753a731a, 0x9bf400e4, 0xb454642a, 0x247d4264, 0x5898ea99, 0x1fc616fe,
	0xa9ac2768, 0x6e39add4, 0xe55532b6, 0x282e81c7, 0x88274050, 0x9f07a9bf, 0x7f73dc11, 0x4be9e37f,
	0xd05d2317, 0xa0d030ee, 0x8809d23a, 0xc49b29c6, 0x83c852b2, 0xf8f77eed, 0x0d75bb83, 0x471b8525,
	0x0a9fdeb8, 0x1bb38936, 0x879617c3, 0xe0e48fc7, 0x8b925ba9, 0x0572c0a7, 0xf240bd8a, 0xf5360956,
	0xbab4b6a0, 0x1f76e976, 0xfe291ba8, 0xe7247522, 0x17e7941e, 0x3c70e2b8, 0xe236a01d, 0x80ea831f,
	0x49438f62, 0x9f9b8ba8, 0x776dc420, 0xdf8df1a9, 0x56394de6, 0x96ec16c8, 0x34e133bb, 0x793063d8,
	0xe943754a, 0x13c02cce, 0x288a739b, 0x76d818f5, 0xffa974cd, 0x9a70c297, 0xb958e6c3, 0x623746f3,
	0xc545e779, 0xa9bf2853, 0xe37faca4, 0x1d839d17, 0x4db19ef3, 0xd12c967d, 0x0863c412, 0x70f41307,
	0x542e1018, 0xfc6d4e03, 0xe73af4e8, 0x9169acd5, 0xb895c569, 0x5cffc773, 0x92fe2c83, 0xdc614d20,
	0x044f7216, 0xb1ddff91, 0xa95cadc6, 0x31d16e5c, 0x4b25ab93, 0x6b57aa0a, 0x80725c92, 0x48ba543a,
	0x2a4bcbe3, 0x19dc6941, 0x742dc1e1, 0x127b5978, 0xcf2f5139, 0x4200c7cd, 0x0927bbe3, 0x6f83d4cc,
	0x26b588f7, 0xbfb5f197, 0xc0461d3c, 0x0f48ddb7, 0x36346d10, 0xae7bdf5f, 0x8af6d28d, 0xa32592d3,
	0xc6e91c60, 0x4bb38468, 0x62c51152, 0x871ab299, 0xbcb5aabd, 0xb6569fbb, 0x8a3efc9c, 0x0925cbdb,
	0x5d4c01f4, 0x278fdb39, 0x019ec177, 0x6f71ed66, 0x819e4fa6, 0x48b94934, 0x8d4ed752, 0xb44611e8,
	0x1f330237, 0x98870a58, 0xc25021a9, 0xe3a055ed, 0xd729cb83, 0xe90f09b6, 0xfe13d01d, 0xfca40a81,
	0x4c714ffc, 0x26c4706a, 0x0db4a005, 0xdb756193, 0x930fda54, 0xfadfcc7e, 0x33767d9e, 0x1fd17e63,
	0x3c5f8035, 0x4b387293, 0x016380c0, 0x8714d2f8, 0x2ce6d1f2, 0x6c729646, 0xf3110f60, 0x141dab38,
	0x7d8b93cf, 0x7d11e3b4, 0xbb212035, 0x951b2e18, 0xa0b0c829, 0xeceb0564, 0x2c1f0975, 0xab2a322c,
	0xc5ef2d19, 0xae16b45d, 0x417187f0, 0x04f66c91, 0x3428ad74, 0x6d4d186e, 0x13626add, 0xb3f51bf5,
	0xd98bed11, 0xbfb6fcf5, 0xe10d70dc, 0x0a41a77c, 0x56a46be4, 0xa29ffe61, 0x71779006, 0xeeda4e52,
	0x9a92daff, 0x6708e033, 0x0f849859, 0x32ca4ca1, 0xc54c08f5, 0x63100a4e, 0x9928d577, 0x68f0ee5c,
	0x56a1793c, 0x616da53a, 0x86231676, 0xe7247242, 0xf7f790fe, 0x40d677c5, 0x200ad649, 0x3fcc384e,
	0xc323e3cf, 0xcf5570e3, 0x0dd24142, 0x2fe694f3, 0x1932be2f, 0x88a40eb5, 0xc241ca13, 0x5d5a70ff,
	0x174f419e, 0xf8880621, 0x4f6b4c77, 0x44ff03be, 0x85967f3b, 0x60718586, 0xa0b77327, 0x9b6e4777,
	0xa113a5d1, 0xf1904dab, 0xff81b230, 0xe7905b56, 0xe33e3899, 0xbef2622b, 0x3f84aab9, 0x04e65fdd,
	0x2defa48e, 0x998f956d, 0x3c458dac, 0x6ea760a7, 0xb7c8625e, 0x4d3df6d5, 0xb903c20f, 0xa50812fe,
	0xecc6c4f3, 0x238eb8df, 0xc50c0f4d, 0xf2ace564, 0x46ed59e9, 0x677d5c3d, 0xf4209535, 0x2fe9e2d1,
	0x057bd2c3, 0x483d3772, 0xdf2a5528, 0xab9ab2ed, 0xe8237cb0, 0x33f12e0b, 0x9f4e4b6e, 0xe684117d,
	0x6ac0d7da, 0x2f6d9829, 0x3dd3cb49, 0x392dcd0b, 0x885c816f, 0x23ffccdf, 0x2000d5db, 0xa63631ab,
	0x45383459, 0xf6b5799d, 0xca7a5458, 0x99313dd9, 0x48a93546, 0x46d10b6a, 0x0d133723, 0x14b2ddf7,
	0x0b1bf566, 0x78789d43, 0x5dfe0a72, 0xdaa41483, 0x0cedc6f2, 0x96adaacc, 0xb9e01bc6, 0x1d27ab55,
	0x3023cb75, 0xcbcfe0f4, 0x70a1fb68, 0x637aed5b, 0x6e314675, 0x41343eff, 0xa2c7afb2, 0xe1663a29,
	0x6132d33e, 0x136673c4, 0xf44d0f30, 0x31742655, 0x986a4c9c, 0xfb8c3ae3, 0x24165f08, 0xd7cf3657,
	0x8d3585be, 0x3e1c4471, 0x32cf23ee, 0x1fd8a4df, 0x1a4c09b3, 0xf58ef6f6, 0xd54d0c33, 0x2beb1121,
	0x445e0fff, 0x444772db, 0xf4b0ad1f, 0x581ba06d, 0x74511c4e, 0x810db2ac, 0x16b16f5d, 0xdbddfb70,
	0xc54c5636, 0x475aa001, 0x5bb012a9, 0x2480bb9f, 0x449ef7e3, 0xfe5a24d6, 0x9b74db5c, 0x3c5cd833,
	0xeb5299ef, 0x9b755512, 0x9b4a3a86, 0xf7343d97, 0xb464312d, 0xb2d83c33, 0x2f3b842d, 0x166d5f4a,
	0xf6545db9, 0x22517187, 0x1a0d6832, 0xd45f6453, 0x640433f0, 0x30ccb1eb, 0xc9229ea2, 0x17bad5b0,
	0x969b7de5, 0xf4751ec0, 0xac7f08f5, 0xc72545cc, 0x61ba30c4, 0xe9c2f7a6, 0xb80bb321, 0x07ac3c43,
	0x67b69894, 0x7fe72d45, 0x3282fda3, 0xcdf34a3f, 0xda4f4f1b, 0x61956b19, 0x4cc096ee, 0x56d78bec,
	0xa12ac0d8, 0x3cfb8e12, 0x4b9de3a7, 0xb57f956d, 0x1035ac44, 0x768788b4, 0x8c6518b4, 0xeced2c80,
	0xef88790f, 0x73cdb03a, 0x860042b4, 0xacfb7bd0, 0x901faf63, 0x1d4103be, 0x712b1972, 0x126d7acd,
	0x4a62e0b0, 0x8d1e7030, 0x4bd046f6, 0x9b6bd869, 0x8f25bd62, 0x025a70c1, 0x4ed48ecd, 0x6bf34186,
	0xf9236a8c, 0xe3f4b8ba, 0x400e809d, 0xec549273, 0xfd9fecf2, 0x0a01706d, 0xb2d7f8b6, 0x63fc97f9,
	0x19b68134, 0xc6a780fa, 0xce028e76, 0x2da664b3, 0xbee8da8b, 0xa9c77a7b, 0xb308f93e, 0xf8d8cf7b,
	0xf9ecedc0, 0x2993ae69, 0x9ddb473b, 0xce033c74, 0x953a9ff8, 0x291845b4, 0x7f95e949, 0x10aaec2b,
	0xf10c5ab8, 0x1f8dc7ce, 0x0f8c8fe6, 0x84545df0, 0xf08e69ba, 0x2b79bb6c, 0xf969de51, 0xbfd97503,
	0xa187339b, 0x720cbf45, 0x5d11ceea, 0x788f3ad5, 0x3f862839, 0xf097ec32, 0x25bacd66, 0xcf8123a4,
	0xbc85fe62, 0x98389971, 0x1feafdbe, 0x6e3aa911, 0x496a52f7, 0xa3112d52, 0x2fd6b5d1, 0x6ab75c84,
	0xd4c433ed, 0xace4aeb5, 0x8e8dd0d9, 0xce9c5cce, 0x94314650, 0x5314f6e4, 0xbd5e71b3, 0x65c4fe65,
	0xee7fe182, 0x639daa2e, 0x4b8521aa, 0x22e72e23, 0x3d19441b, 0x8f6dda32, 0x201e0652, 0x3ee1fba4,
	0x01fa8834, 0x2b629df1, 0xaf31253b, 0xe7c7c696, 0x90d0057a, 0x60afee77, 0x5d31f4b6, 0x3aea99c2,
	0xf6bc2f1b, 0xf441f21a, 0xd55c58da, 0xec9523a6, 0x72f90c36, 0x9a35a68f, 0x70defd35, 0xfd958b7c,
	0x0e3f32b0, 0xcd11f11c, 0x197df60d, 0x657e9356, 0xa6c8e644, 0x008d202c, 0xe052084a, 0x19f687f8,
	0x278dc56c, 0x378f8f93, 0x01ea381d, 0xe2e6410d, 0x17d88078, 0x1ad6efc1, 0x31928b6b, 0xd83b1d6c,
	0x488ff440, 0x8b2d5594, 0xc5ef7b4b, 0x8d599c6f, 0xb61bc570, 0xd378432b, 0xfa8775f9, 0x876cd01c,
	0x339e5ab5, 0x7ab25871, 0x87fa4f9d, 0xf40fdae4, 0xbe18fe21, 0xacbb74cc, 0xf772c1f9, 0xb9dcee02,
	0x26aa8c30, 0x62ff2345, 0x60e5a9be, 0xd499bd76, 0x65c2316f, 0xef094ec0, 0xa70c4972, 0x2b9fdcc6,
	0xcdaac587, 0xcfb81017, 0x936ea038, 0xb5d13a51, 0x3395a8b4, 0x522150b3, 0xb426aff0, 0x75b9e3cf,
	0xb19e6d19, 0x60c2439f, 0xb576e261, 0x55750929, 0x491542c9, 0xe2dde75c, 0x04bd8859, 0xa877245a,
	0x2f2e6123, 0xf31522b9, 0x4f7858fb, 0x7a72d4f3, 0xe4763730, 0x7f0ef9b8, 0x8e0e172f, 0x9cdcd418,
	0x32fd7515, 0xe011097c, 0x3b85e900, 0x52cc43fc, 0x59eaa33e, 0x90ed5576, 0x037cd9eb, 0x6a13f637,
	0xea060f44, 0x70a46e5a, 0x8f34e404, 0x7679952c, 0xe99219ee, 0x2bf21f64, 0x946a5da7, 0xd2d80948,
	0xe1737219, 0xfc361062, 0x27c52933, 0x5110b925, 0x58e1d2ef, 0x16c9da3c, 0x30b332cb, 0xe5a32282,
	0xacaae671, 0x8fa8d5c8, 0x63c02a21, 0x7f597e7e, 0x83e090a7, 0x9ed6679a, 0x95e73663, 0x5ebe3a4c,
	0xa326b2d3, 0x2f69d012, 0x75d66178, 0xbc01722e, 0x0355aa35, 0xa703a695, 0xf0c6f538, 0xc89bd3e5,
	0x74233b3c, 0xfa49e7c4, 0x1a3ece7b, 0xa39a766b, 0xc2fe57eb, 0x6f5ba8ce, 0x6ca68926, 0xe360068d,
	0x6b4a1661, 0x3e1a4cb3, 0x3c1c8245, 0x449e4f58, 0x99b15361, 0x009cb03e, 0x943c1d93, 0xf6836ffd,
	0xe06fe98d, 0x962c10c1, 0x917f04ce, 0x572c9314, 0x0c289d86, 0x3c97a399, 0xe20bcf74, 0x96d45868,
	0x1ab9b08b, 0xbfad0c84, 0xeb88c7af, 0xb84e3582, 0x4d99ef39, 0xb69e2941, 0x7993f05d, 0x850092d5,
	0xb60a8d66, 0x13799992, 0xf3e34b60, 0x0b5720be, 0xf9503bde, 0x3d844d75, 0x50b43492, 0x65447273,
	0x721f397f, 0x54fdc1f7, 0x514c5e0c, 0xdaa9821d, 0x88fd313c, 0xa68378fa, 0x5bea4dbd, 0xe8a5ed79,
	0xa6b04c58, 0x2efc7e52, 0xeaa21191, 0x64eb8395, 0xd061cefa, 0x9b5c9e8a, 0x7a26c9f0, 0x89bb16be,
	0xb5c4b7f1, 0x1a27f5da, 0x9667000d, 0xeb4176e7, 0x89499a5d, 0x12347588, 0x6fa9b976, 0x24ed60b2,
	0xc5832645, 0x26c4d2d7, 0xfe065cb3, 0x8ca9171e, 0xf6a1e8e3, 0x5d33a7c3, 0x3de2fcf4, 0x8edff93e,
	0x3c0f41b6, 0x0873955d, 0xe0d5dc32, 0x41589aaf, 0xf81e6784, 0x0900d355, 0xcd3bd5eb, 0x927c318f,
	0x6d35bc2a, 0x9b024fb1, 0xc6f37849, 0xefc7bee2, 0xc6252408, 0x874de849, 0xb84f95a0, 0x605d49d4,
	0x51bfafab, 0x93ed8661, 0xbbca5e8e, 0x59c98ea6, 0x53e634a4, 0xd91ab96d, 0x82876d30, 0x6a0f94fd,
	0x7de78657, 0x9ede73bd, 0x3da562cc, 0x6ee36a0a, 0x79ad3d6d, 0x25276825, 0xcc050fd7, 0x7d98a5e2,
	0x41581a92, 0x2556af1d, 0x580b3661, 0x27df2e4b, 0x0d254a6d, 0xff784ad3, 0x60e1d921, 0x71b9d42c,
	0xc5c9c1c1, 0x15c24f15, 0xc92a4d83, 0xf2f6c218, 0xde3dc88f, 0x38a58963, 0xf588c4dd, 0x99ece9bf,
	0xff5d0550, 0xdfcbb95a, 0x287c66db, 0xd75d4320, 0xecbc37e5, 0x9a81de13, 0x06a932e3, 0x5be55504,
	0xcd9edd53, 0x1bda50bb, 0xe4070b2a, 0x73f9c932, 0x27ff9c3a, 0x5a0add63, 0xeb30c423, 0x756628d0,
	0x52c57ea4, 0x09d25155, 0x7a346a18, 0xde7d7938, 0xbeafe38d, 0x9d5fab7a, 0x077914ef, 0x775d24af,
	0x0d7d8f57, 0xc6f53037, 0x2e75b0b9, 0x97f751c5, 0x5d48ced7, 0xa4f359f0, 0x08db3219, 0x6e87f712,
	0x9c8432d3, 0xcf90e91d, 0x0eff78f3, 0xfb2b5575, 0x4b7c776a, 0xc329058e, 0x78a191dc, 0x52a7d79a,
	0xf87ec816, 0xad9ba277, 0x6b38272a, 0x5a35b72e, 0xa83aa648, 0x2cae7f1f, 0x528a8ef7, 0x8421c12a,
	0x3646f0a8, 0x0faffff1, 0x7409a103, 0x61253285, 0xcb8511e4, 0x1817ae65, 0xb6836a1c, 0x1b09b909,
	0x3e219a00, 0x44fd3b25, 0x2f163e50, 0x5717a726, 0xe33f24e0, 0x70fcd98e, 0x06f752fd, 0x15eb5254,
	0x96c86967, 0xb307b72a, 0xa0c60d8a, 0x9bd6423d, 0x5e9b29c7, 0x420532c5, 0x3a44351e, 0x10555df3,
	0xee54de63, 0x4c5ae08a, 0x88e35d49, 0xf6aae4dc, 0x918a0e63, 0x87c75f7b, 0xfaeba338, 0x893c025a,
	0x9183778e, 0xb7281ddd, 0xf9709768, 0x4e0a4b56, 0x41070b15, 0x4b989281, 0xc05b0973, 0x444d4eac,
	0x09bd2bff, 0x70f333b1, 0x03fb9352, 0xc0f89d15, 0xef5c2e6d, 0xc69c3445, 0xb4068166, 0xa5551ee9,
	0x1ba33368, 0x0bf6009e, 0x16111132, 0x471fa3f5, 0x62755fc7, 0x45424bad, 0x6b9a7016, 0x6a2da875,
	0xf67dc21b, 0x1b0273d8, 0xef3b376b, 0x254d485c, 0x38ed0004, 0xd0e47e5c, 0x1123820f, 0x013e5c0b,
	0x3b89949f, 0x966d7ad0, 0x47d85c77, 0xae6ae677, 0x14bd60fd, 0xef5cd430, 0x5f7b6917, 0xbbe8e7ff,
	0x2325c0ae, 0x7ffc3216, 0x8b66cbaf, 0xfcea07a8, 0xc662f100, 0x8abfe8f2, 0x666777e3, 0x190513a9,
	0x83fb3a64, 0xc70a532f, 0x84307ada, 0x163f1f38, 0x2b191f63, 0x7aa5d6f3, 0x9bfdc5c2, 0x4aec76ac,
	0xd7ed57ff, 0x4d04f9e2, 0x2bf7272d, 0xb061b7f9, 0x78ac4f66, 0x14bb6ad0, 0xff138cf6, 0x6f9c574d,
	0xf3cfd513, 0x1a1650ea, 0xde73cc03, 0x722df85a, 0xf342b210, 0x305f0371, 0x86b716ad, 0x64e8c7ba,
	0xd4eeffc4, 0x401f8369, 0x41a0a4ad, 0xd2bafa61, 0x08b838a2, 0xfc08346d, 0xef4aeede, 0xe4ca1d9b,
	0x2c3d14bd, 0x78041906, 0xfbda3acc, 0xc593b3e0, 0x26b74690, 0xe6c55b49, 0x250173ba, 0x8edff7db,
	0x0fcb0618, 0x49ac76b3, 0xc37c6132, 0xadc16586, 0xa88bb0e1, 0x1f2ebbd8, 0x34909c53, 0xedd4c888,
	0x6eaf1cf9, 0xb18931c8, 0xaa8c98d4, 0xd3fa25ea, 0xd2079a50, 0x80e3c119, 0xd753e5a5, 0xcc48b052,
	0xa6994729, 0x46bcdf34, 0x684c8ce3, 0x41aa0a8b, 0x55f1fa43, 0x376d9e79, 0xae68a1b5, 0x0a5aecd7,
	0x5303cd2b, 0x1e72a546, 0xbc7e7dec, 0x12cad2ea, 0x811de6db, 0x8e58eea2, 0xa09f3fb0, 0x6c6b6878,
	0xb43cfafd, 0x56a580c4, 0x3a220e5a, 0xc3cf2c6e, 0x3160645c, 0x424dc638, 0xea3fb77d, 0xe0e56c1d,
	0x2be076a1, 0xefe70359, 0x5c8e0152, 0x7c65cbed, 0x0b1b0035, 0x8127c3fe, 0x07b84775, 0xa872b8b4,
	0xe01c1d8f, 0x33ba847d, 0xf3578423, 0x5bdfe69b, 0xdfb005ba, 0xc82280fa, 0xa5dc0001, 0x3143c4c3,
	0x422c664d, 0x108427dd, 0x2ee4444f, 0xc97c3cca, 0x5dc99faa, 0x87dc76e5, 0xe1240a9b, 0xc55406e1,
	0xca74b2ab, 0x8fc03f22, 0xe4a6c66e, 0xde8a2070, 0x0430530c, 0xc64ef18f, 0x03aa83c9, 0x393318eb,
	0x7eb836cf, 0xab47748a, 0x53e33ee4, 0xbaf5b959, 0x5b9dcf8b, 0x613cd3f3, 0xf36305d8, 0x8270bebd,
	0xcffd7f01, 0xbf23a2f1, 0x56a5bacf, 0x474eebfd, 0x6707302e, 0x69ff5b24, 0xfa06f1f4, 0x9a69f0b5,
	0x24619433, 0x14294bf9, 0x7bb3da25, 0xc30d8f90, 0xcdc08f31, 0xa088520a, 0x2c9fa964, 0x2a8cfaa0,
	0xc88d3b98, 0xdfd98f17, 0x0aff1278, 0xd1f1891f, 0x9ebc365e, 0xb47dfef1, 0x0f2e5cb8, 0x3246d39e,
	0x8c16d9c7, 0x37e4c14e, 0x693e7a66, 0x2d4ecd60, 0x596a970d, 0x5bd491bf, 0x3f1e7bc1, 0xcf1b55ba,
	0x41284a90, 0x78b69a20, 0x26ef6c9d, 0x0ab8c2dd, 0x02b48cfb, 0xd0b736ea, 0x0d4f50ef, 0x617d1635,
	0x3cdf6685, 0xf9f6f244, 0x05f829ef, 0x8ebe56d4, 0x5f0b655d, 0x5f227896, 0xf5806d85, 0xe0edc470,
	0xedf153ad, 0x14eda5eb, 0xe648e809, 0xbbeedfda, 0xb8f5e959, 0x975d59b1, 0x00eba227, 0xbc148c77,
	0xc6e000f5, 0x5e87f8c1, 0xc315a389, 0xfc60f6f9, 0xd48162ef, 0x4bacebe8, 0xc61f8d75, 0x4c9af151,
	0xd323c646, 0x1b3fd960, 0x0b6555bc, 0x8dee368b, 0x6cdfba3e, 0x0c7c49a5, 0xbbae6bac, 0xb385d7b7
};

#endif
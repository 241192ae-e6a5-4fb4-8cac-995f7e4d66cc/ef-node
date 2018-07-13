#pragma once

#include <cstdint>
#include <cstdlib>

namespace NEvenFound::NMeta {

namespace NImpl {

static constexpr uint64_t Tab[] = {
    0x0000000000000000ull, 0x7ad870c830358979ull, 0xf5b0e190606b12f2ull, 0x8f689158505e9b8bull,
    0xc038e5739841b68full, 0xbae095bba8743ff6ull, 0x358804e3f82aa47dull, 0x4f50742bc81f2d04ull,
    0xab28ecb46814fe75ull, 0xd1f09c7c5821770cull, 0x5e980d24087fec87ull, 0x24407dec384a65feull,
    0x6b1009c7f05548faull, 0x11c8790fc060c183ull, 0x9ea0e857903e5a08ull, 0xe478989fa00bd371ull,
    0x7d08ff3b88be6f81ull, 0x07d08ff3b88be6f8ull, 0x88b81eabe8d57d73ull, 0xf2606e63d8e0f40aull,
    0xbd301a4810ffd90eull, 0xc7e86a8020ca5077ull, 0x4880fbd87094cbfcull, 0x32588b1040a14285ull,
    0xd620138fe0aa91f4ull, 0xacf86347d09f188dull, 0x2390f21f80c18306ull, 0x594882d7b0f40a7full,
    0x1618f6fc78eb277bull, 0x6cc0863448deae02ull, 0xe3a8176c18803589ull, 0x997067a428b5bcf0ull,
    0xfa11fe77117cdf02ull, 0x80c98ebf2149567bull, 0x0fa11fe77117cdf0ull, 0x75796f2f41224489ull,
    0x3a291b04893d698dull, 0x40f16bccb908e0f4ull, 0xcf99fa94e9567b7full, 0xb5418a5cd963f206ull,
    0x513912c379682177ull, 0x2be1620b495da80eull, 0xa489f35319033385ull, 0xde51839b2936bafcull,
    0x9101f7b0e12997f8ull, 0xebd98778d11c1e81ull, 0x64b116208142850aull, 0x1e6966e8b1770c73ull,
    0x8719014c99c2b083ull, 0xfdc17184a9f739faull, 0x72a9e0dcf9a9a271ull, 0x08719014c99c2b08ull,
    0x4721e43f0183060cull, 0x3df994f731b68f75ull, 0xb29105af61e814feull, 0xc849756751dd9d87ull,
    0x2c31edf8f1d64ef6ull, 0x56e99d30c1e3c78full, 0xd9810c6891bd5c04ull, 0xa3597ca0a188d57dull,
    0xec09088b6997f879ull, 0x96d1784359a27100ull, 0x19b9e91b09fcea8bull, 0x636199d339c963f2ull,
    0xdf7adabd7a6e2d6full, 0xa5a2aa754a5ba416ull, 0x2aca3b2d1a053f9dull, 0x50124be52a30b6e4ull,
    0x1f423fcee22f9be0ull, 0x659a4f06d21a1299ull, 0xeaf2de5e82448912ull, 0x902aae96b271006bull,
    0x74523609127ad31aull, 0x0e8a46c1224f5a63ull, 0x81e2d7997211c1e8ull, 0xfb3aa75142244891ull,
    0xb46ad37a8a3b6595ull, 0xceb2a3b2ba0eececull, 0x41da32eaea507767ull, 0x3b024222da65fe1eull,
    0xa2722586f2d042eeull, 0xd8aa554ec2e5cb97ull, 0x57c2c41692bb501cull, 0x2d1ab4dea28ed965ull,
    0x624ac0f56a91f461ull, 0x1892b03d5aa47d18ull, 0x97fa21650afae693ull, 0xed2251ad3acf6feaull,
    0x095ac9329ac4bc9bull, 0x7382b9faaaf135e2ull, 0xfcea28a2faafae69ull, 0x8632586aca9a2710ull,
    0xc9622c4102850a14ull, 0xb3ba5c8932b0836dull, 0x3cd2cdd162ee18e6ull, 0x460abd1952db919full,
    0x256b24ca6b12f26dull, 0x5fb354025b277b14ull, 0xd0dbc55a0b79e09full, 0xaa03b5923b4c69e6ull,
    0xe553c1b9f35344e2ull, 0x9f8bb171c366cd9bull, 0x10e3202993385610ull, 0x6a3b50e1a30ddf69ull,
    0x8e43c87e03060c18ull, 0xf49bb8b633338561ull, 0x7bf329ee636d1eeaull, 0x012b592653589793ull,
    0x4e7b2d0d9b47ba97ull, 0x34a35dc5ab7233eeull, 0xbbcbcc9dfb2ca865ull, 0xc113bc55cb19211cull,
    0x5863dbf1e3ac9decull, 0x22bbab39d3991495ull, 0xadd33a6183c78f1eull, 0xd70b4aa9b3f20667ull,
    0x985b3e827bed2b63ull, 0xe2834e4a4bd8a21aull, 0x6debdf121b863991ull, 0x1733afda2bb3b0e8ull,
    0xf34b37458bb86399ull, 0x8993478dbb8deae0ull, 0x06fbd6d5ebd3716bull, 0x7c23a61ddbe6f812ull,
    0x3373d23613f9d516ull, 0x49aba2fe23cc5c6full, 0xc6c333a67392c7e4ull, 0xbc1b436e43a74e9dull,
    0x95ac9329ac4bc9b5ull, 0xef74e3e19c7e40ccull, 0x601c72b9cc20db47ull, 0x1ac40271fc15523eull,
    0x5594765a340a7f3aull, 0x2f4c0692043ff643ull, 0xa02497ca54616dc8ull, 0xdafce7026454e4b1ull,
    0x3e847f9dc45f37c0ull, 0x445c0f55f46abeb9ull, 0xcb349e0da4342532ull, 0xb1eceec59401ac4bull,
    0xfebc9aee5c1e814full, 0x8464ea266c2b0836ull, 0x0b0c7b7e3c7593bdull, 0x71d40bb60c401ac4ull,
    0xe8a46c1224f5a634ull, 0x927c1cda14c02f4dull, 0x1d148d82449eb4c6ull, 0x67ccfd4a74ab3dbfull,
    0x289c8961bcb410bbull, 0x5244f9a98c8199c2ull, 0xdd2c68f1dcdf0249ull, 0xa7f41839ecea8b30ull,
    0x438c80a64ce15841ull, 0x3954f06e7cd4d138ull, 0xb63c61362c8a4ab3ull, 0xcce411fe1cbfc3caull,
    0x83b465d5d4a0eeceull, 0xf96c151de49567b7ull, 0x76048445b4cbfc3cull, 0x0cdcf48d84fe7545ull,
    0x6fbd6d5ebd3716b7ull, 0x15651d968d029fceull, 0x9a0d8ccedd5c0445ull, 0xe0d5fc06ed698d3cull,
    0xaf85882d2576a038ull, 0xd55df8e515432941ull, 0x5a3569bd451db2caull, 0x20ed197575283bb3ull,
    0xc49581ead523e8c2ull, 0xbe4df122e51661bbull, 0x3125607ab548fa30ull, 0x4bfd10b2857d7349ull,
    0x04ad64994d625e4dull, 0x7e7514517d57d734ull, 0xf11d85092d094cbfull, 0x8bc5f5c11d3cc5c6ull,
    0x12b5926535897936ull, 0x686de2ad05bcf04full, 0xe70573f555e26bc4ull, 0x9ddd033d65d7e2bdull,
    0xd28d7716adc8cfb9ull, 0xa85507de9dfd46c0ull, 0x273d9686cda3dd4bull, 0x5de5e64efd965432ull,
    0xb99d7ed15d9d8743ull, 0xc3450e196da80e3aull, 0x4c2d9f413df695b1ull, 0x36f5ef890dc31cc8ull,
    0x79a59ba2c5dc31ccull, 0x037deb6af5e9b8b5ull, 0x8c157a32a5b7233eull, 0xf6cd0afa9582aa47ull,
    0x4ad64994d625e4daull, 0x300e395ce6106da3ull, 0xbf66a804b64ef628ull, 0xc5bed8cc867b7f51ull,
    0x8aeeace74e645255ull, 0xf036dc2f7e51db2cull, 0x7f5e4d772e0f40a7ull, 0x05863dbf1e3ac9deull,
    0xe1fea520be311aafull, 0x9b26d5e88e0493d6ull, 0x144e44b0de5a085dull, 0x6e963478ee6f8124ull,
    0x21c640532670ac20ull, 0x5b1e309b16452559ull, 0xd476a1c3461bbed2ull, 0xaeaed10b762e37abull,
    0x37deb6af5e9b8b5bull, 0x4d06c6676eae0222ull, 0xc26e573f3ef099a9ull, 0xb8b627f70ec510d0ull,
    0xf7e653dcc6da3dd4ull, 0x8d3e2314f6efb4adull, 0x0256b24ca6b12f26ull, 0x788ec2849684a65full,
    0x9cf65a1b368f752eull, 0xe62e2ad306bafc57ull, 0x6946bb8b56e467dcull, 0x139ecb4366d1eea5ull,
    0x5ccebf68aecec3a1ull, 0x2616cfa09efb4ad8ull, 0xa97e5ef8cea5d153ull, 0xd3a62e30fe90582aull,
    0xb0c7b7e3c7593bd8ull, 0xca1fc72bf76cb2a1ull, 0x45775673a732292aull, 0x3faf26bb9707a053ull,
    0x70ff52905f188d57ull, 0x0a2722586f2d042eull, 0x854fb3003f739fa5ull, 0xff97c3c80f4616dcull,
    0x1bef5b57af4dc5adull, 0x61372b9f9f784cd4ull, 0xee5fbac7cf26d75full, 0x9487ca0fff135e26ull,
    0xdbd7be24370c7322ull, 0xa10fceec0739fa5bull, 0x2e675fb4576761d0ull, 0x54bf2f7c6752e8a9ull,
    0xcdcf48d84fe75459ull, 0xb71738107fd2dd20ull, 0x387fa9482f8c46abull, 0x42a7d9801fb9cfd2ull,
    0x0df7adabd7a6e2d6ull, 0x772fdd63e7936bafull, 0xf8474c3bb7cdf024ull, 0x829f3cf387f8795dull,
    0x66e7a46c27f3aa2cull, 0x1c3fd4a417c62355ull, 0x935745fc4798b8deull, 0xe98f353477ad31a7ull,
    0xa6df411fbfb21ca3ull, 0xdc0731d78f8795daull, 0x536fa08fdfd90e51ull, 0x29b7d047efec8728ull,
};


static constexpr size_t StrLen(const char *str, size_t acc) {
    return (*str) ? StrLen(str + 1, acc + 1) : acc; 
}

static constexpr uint64_t CRC64(const char *str, size_t size, uint64_t acc) {
    return (size > 0) ? CRC64(str + 1, size - 1, Tab[((acc) ^ (str[0])) & 0xFF] ^ ((acc) >> 8)) : acc;
}

}   // namespace NImpl

static constexpr uint64_t CRC64(const char *str) {
    return NImpl::CRC64(str, NImpl::StrLen(str, 0), 0);
}

}   // namespace NEvenFound::NMeta


FIND_PROGRAM(OPENSSL_PROGRAM NAMES openssl)
MESSAGE(STATUS "OPENSSL_PROGRAM    => ${OPENSSL_PROGRAM}")


ADD_CUSTOM_COMMAND(
    OUTPUT ${EF_KEYS_DIR}
    COMMAND mkdir -p ${EF_KEYS_DIR}
    COMMENT "Create private keys directory"
    VERBATIM
)


ADD_CUSTOM_COMMAND(
    OUTPUT ${EF_PUBKEYS_DIR}
    COMMAND mkdir -p ${EF_PUBKEYS_DIR}
    COMMENT "Create public keys directory"
    VERBATIM
)


MACRO(EF_CREATE_KEYPAIR node)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${EF_KEYS_DIR}/${node}.key ${EF_PUBKEYS_DIR}/${node}_pub.key
        COMMAND ${OPENSSL_PROGRAM} genrsa -out ${EF_KEYS_DIR}/${node}.pem ${EF_RSA_KEY_LENGTH}
        COMMAND ${OPENSSL_PROGRAM} rsa -in ${EF_KEYS_DIR}/${node}.pem -outform DER -out ${EF_KEYS_DIR}/${node}.key
        COMMAND ${OPENSSL_PROGRAM} rsa -in ${EF_KEYS_DIR}/${node}.pem -RSAPublicKey_out -outform DER -out ${EF_PUBKEYS_DIR}/${node}_pub.key
        DEPENDS ${EF_KEYS_DIR} ${EF_PUBKEYS_DIR}
        COMMENT "Generate key pair for node ${node}"
        VERBATIM
    )
    ADD_CUSTOM_TARGET(${node}_keypair ALL
        DEPENDS ${EF_KEYS_DIR}/${node}.key ${EF_PUBKEYS_DIR}/${node}_pub.key
    )
ENDMACRO(EF_CREATE_KEYPAIR)


EF_CREATE_KEYPAIR(alpha)
EF_CREATE_KEYPAIR(beta)
EF_CREATE_KEYPAIR(test)

CONFIGURE_FILE(config.hpp.in ${EF_GEN_INCLUDE_DIR}/evenfound/config.hpp)

CONFIGURE_FILE(start_alpha.sh.in ${CMAKE_BINARY_DIR}/start_alpha.sh)
CONFIGURE_FILE(start_beta.sh.in ${CMAKE_BINARY_DIR}/start_beta.sh)

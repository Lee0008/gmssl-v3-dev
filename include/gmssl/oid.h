﻿/*
 * Copyright (c) 2014 - 2021 The GmSSL Project.  All rights reserved.
 *
OCSPSigning * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef GMSSL_OID_H
#define GMSSL_OID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	OID_undef = 0,

	// ShangMi schemes in GM/T 0006-2012
	OID_sm1,
	OID_ssf33,
	OID_sm4,
	OID_zuc,
	OID_sm2,
	OID_sm2sign,
	OID_sm2keyagreement,
	OID_sm2encrypt,
	OID_sm9,
	OID_sm9sign,
	OID_sm9keyagreement,
	OID_sm9encrypt,
	OID_sm3,
	OID_sm3_keyless,
	OID_hmac_sm3,
	OID_sm2sign_with_sm3,
	OID_rsasign_with_sm3,
	OID_ec_public_key, // X9.62 ecPublicKey
	OID_prime192v1,
	OID_prime256v1,
	OID_secp256k1,
	OID_secp192k1,
	OID_secp224k1,
	OID_secp224r1,
	OID_secp384r1,
	OID_secp521r1,

	OID_at_name,
	OID_at_surname,
	OID_at_given_name,
	OID_at_initials,
	OID_at_generation_qualifier,
	OID_at_common_name,
	OID_at_locality_name,
	OID_at_state_or_province_name,
	OID_at_organization_name,
	OID_at_organizational_unit_name,
	OID_at_title,
	OID_at_dn_qualifier,
	OID_at_country_name,
	OID_at_serial_number,
	OID_at_pseudonym,
	OID_domain_component,

	// Cert Extensions
	OID_ce_authority_key_identifier,
	OID_ce_subject_key_identifier,
	OID_ce_key_usage,
	OID_ce_certificate_policies,
	OID_ce_policy_mappings,
	OID_ce_subject_alt_name,
	OID_ce_issuer_alt_name,
	OID_ce_subject_directory_attributes,
	OID_ce_basic_constraints,
	OID_ce_name_constraints,
	OID_ce_policy_constraints,
	OID_ce_ext_key_usage,
	OID_ce_crl_distribution_points,
	OID_ce_inhibit_any_policy,
	OID_ce_freshest_crl,

	// CRL Extensions
	//OID_ce_authority_key_identifier,
	//OID_ce_issuer_alt_name,
	OID_ce_crl_number,
	OID_ce_delta_crl_indicator,
	OID_ce_issuing_distribution_point,
	//OID_ce_freshest_crl,
	OID_pe_authority_info_access,

	// CRL Entry Extensions
	OID_ce_crl_reasons,
	OID_ce_invalidity_date,
	OID_ce_certificate_issuer,

	// X.509 KeyPropuseID
	OID_kp_server_auth,
	OID_kp_client_auth,
	OID_kp_code_signing,
	OID_kp_email_protection,
	OID_kp_time_stamping,
	OID_kp_ocsp_signing,

	OID_qt_cps,
	OID_qt_unotice,

	OID_md5,
	OID_sha1,
	OID_sha224,
	OID_sha256,
	OID_sha384,
	OID_sha512,
	OID_sha512_224,
	OID_sha512_256,

	OID_pbkdf2, // {pkcs-5 12}
	OID_pbes2,  // {pkcs-5 13}
	OID_hmacWithSHA1,
	OID_hmacWithSHA224,

	OID_sm4_ecb, // 1 2 156 10197 1 104 1
	OID_sm4_cbc, // 1 2 156 10197 1 104 2

	OID_aes,
	OID_aes128_cbc,
	OID_aes192_cbc,
	OID_aes256_cbc,

	OID_aes128, // 没有OID

	OID_ecdsa_with_sha1,
	OID_ecdsa_with_sha224,
	OID_ecdsa_with_sha256,
	OID_ecdsa_with_sha384,
	OID_ecdsa_with_sha512,

	OID_rsasign_with_sha1,
	OID_rsasign_with_sha224,
	OID_rsasign_with_sha256,
	OID_rsasign_with_sha384,
	OID_rsasign_with_sha512,

	OID_rsa_encryption,
	OID_rsaes_oaep,

	OID_any_policy,

	OID_cms_data,
	OID_cms_signed_data,
	OID_cms_enveloped_data,
	OID_cms_signed_and_enveloped_data,
	OID_cms_encrypted_data,
	OID_cms_key_agreement_info,
};



#define oid_pkix 1,3,6,1,5,5,7

#define oid_pe	oid_pkix,1
#define oid_qt	oid_pkix,2
#define oid_kp	oid_pkix,3
#define oid_ad	oid_pkix,48


#define oid_at	2,5,4
#define oid_ce	2,5,29


#define oid_sm2_cms 1,2,156,10197,6,1,4,2


#ifdef __cplusplus
}
#endif
#endif

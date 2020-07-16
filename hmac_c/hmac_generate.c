
// const br_hash_class *digest_class = &br_sha256_vtable;//choosing the hash type
// br_hmac_key_context kc;
// br_hmac_context ctx;

// br_hmac_key_init(&kc, digest_class, KEY, KEY_LEN);
// br_hmac_init(&ctx, &kc, 0); //sets up the context similar to .new
// br_hmac_update(&ctx, data, data_len); //equal to the update function
// br_hmac_out(&ctx, tmp); //equal to .digest, but fills the hmac into tmp
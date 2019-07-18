/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/*
 * A nice addition from Dr Stephen Henson <steve@openssl.org> to add the
 * -strparse option which parses nested binary structures
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apps.h"
#include BOSS_OPENSSL_V_openssl__err_h //original-code:<openssl/err.h>
#include BOSS_OPENSSL_V_openssl__evp_h //original-code:<openssl/evp.h>
#include BOSS_OPENSSL_V_openssl__x509_h //original-code:<openssl/x509.h>
#include BOSS_OPENSSL_V_openssl__pem_h //original-code:<openssl/pem.h>

typedef enum OPTION_choice {
    OPT_ERR = -1, OPT_EOF = 0, OPT_HELP,
    OPT_INFORM, OPT_IN, OPT_OUT, OPT_INDENT, OPT_NOOUT,
    OPT_OID, OPT_OFFSET, OPT_LENGTH, OPT_DUMP, OPT_DLIMIT,
    OPT_STRPARSE, OPT_GENSTR, OPT_GENCONF, OPT_STRICTPEM
} OPTION_CHOICE;

OPTIONS asn1parse_options[] = {
    {"help", OPT_HELP, '-', "Display this summary"},
    {"inform", OPT_INFORM, 'F', "input format - one of DER PEM"},
    {"in", OPT_IN, '<', "input file"},
    {"out", OPT_OUT, '>', "output file (output format is always DER)"},
    {"i", OPT_INDENT, 0, "indents the output"},
    {"noout", OPT_NOOUT, 0, "do not produce any output"},
    {"offset", OPT_OFFSET, 'p', "offset into file"},
    {"length", OPT_LENGTH, 'p', "length of section in file"},
    {"oid", OPT_OID, '<', "file of extra oid definitions"},
    {"dump", OPT_DUMP, 0, "unknown data in hex form"},
    {"dlimit", OPT_DLIMIT, 'p',
     "dump the first arg bytes of unknown data in hex form"},
    {"strparse", OPT_STRPARSE, 's',
     "offset; a series of these can be used to 'dig'"},
    {OPT_MORE_STR, 0, 0, "into multiple ASN1 blob wrappings"},
    {"genstr", OPT_GENSTR, 's', "string to generate ASN1 structure from"},
    {"genconf", OPT_GENCONF, 's', "file to generate ASN1 structure from"},
    {OPT_MORE_STR, 0, 0, "(-inform  will be ignored)"},
    {"strictpem", OPT_STRICTPEM, 0,
     "do not attempt base64 decode outside PEM markers"},
    {NULL}
};

static int do_generate(char *genstr, const char *genconf, BUF_MEM *buf);

int asn1parse_main(int argc, char **argv)
{
    ASN1_TYPE *at = NULL;
    BIO *in = NULL, *b64 = NULL, *derout = NULL;
    BUF_MEM *buf = NULL;
    STACK_OF(OPENSSL_STRING) *osk = NULL;
    char *genstr = NULL, *genconf = NULL;
    char *infile = NULL, *oidfile = NULL, *derfile = NULL;
    unsigned char *str = NULL;
    char *name = NULL, *header = NULL, *prog;
    const unsigned char *ctmpbuf;
    int indent = 0, noout = 0, dump = 0, strictpem = 0, informat = FORMAT_PEM;
    int offset = 0, ret = 1, i, j;
    long num, tmplen;
    unsigned char *tmpbuf;
    unsigned int length = 0;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, asn1parse_options);

    if ((osk = sk_OPENSSL_STRING_new_null()) == NULL) {
        BIO_printf(bio_err, "%s: Memory allocation failure\n", prog);
        goto end;
    }

    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(asn1parse_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &informat))
                goto opthelp;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            derfile = opt_arg();
            break;
        case OPT_INDENT:
            indent = 1;
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_OID:
            oidfile = opt_arg();
            break;
        case OPT_OFFSET:
            offset = strtol(opt_arg(), NULL, 0);
            break;
        case OPT_LENGTH:
            length = atoi(opt_arg());
            break;
        case OPT_DUMP:
            dump = -1;
            break;
        case OPT_DLIMIT:
            dump = atoi(opt_arg());
            break;
        case OPT_STRPARSE:
            sk_OPENSSL_STRING_push(osk, opt_arg());
            break;
        case OPT_GENSTR:
            genstr = opt_arg();
            break;
        case OPT_GENCONF:
            genconf = opt_arg();
            break;
        case OPT_STRICTPEM:
            strictpem = 1;
            informat = FORMAT_PEM;
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    if (oidfile != NULL) {
        in = bio_open_default(oidfile, 'r', FORMAT_TEXT);
        if (in == NULL)
            goto end;
        OBJ_create_objects(in);
        BIO_free(in);
    }

    if ((in = bio_open_default(infile, 'r', informat)) == NULL)
        goto end;

    if (derfile && (derout = bio_open_default(derfile, 'w', FORMAT_ASN1)) == NULL)
        goto end;

    if (strictpem) {
        if (PEM_read_bio(in, &name, &header, &str, &num) !=
            1) {
            BIO_printf(bio_err, "Error reading PEM file\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    } else {

        if ((buf = BUF_MEM_new()) == NULL)
            goto end;
        if (!BUF_MEM_grow(buf, BUFSIZ * 8))
            goto end;           /* Pre-allocate :-) */

        if (genstr || genconf) {
            num = do_generate(genstr, genconf, buf);
            if (num < 0) {
                ERR_print_errors(bio_err);
                goto end;
            }
        }

        else {

            if (informat == FORMAT_PEM) {
                BIO *tmp;

                if ((b64 = BIO_new(BIO_f_base64())) == NULL)
                    goto end;
                BIO_push(b64, in);
                tmp = in;
                in = b64;
                b64 = tmp;
            }

            num = 0;
            for (;;) {
                if (!BUF_MEM_grow(buf, (int)num + BUFSIZ))
                    goto end;
                i = BIO_read(in, &(buf->data[num]), BUFSIZ);
                if (i <= 0)
                    break;
                num += i;
            }
        }
        str = (unsigned char *)buf->data;

    }

    /* If any structs to parse go through in sequence */

    if (sk_OPENSSL_STRING_num(osk)) {
        tmpbuf = str;
        tmplen = num;
        for (i = 0; i < sk_OPENSSL_STRING_num(osk); i++) {
            ASN1_TYPE *atmp;
            int typ;
            j = atoi(sk_OPENSSL_STRING_value(osk, i));
            if (j == 0) {
                BIO_printf(bio_err, "'%s' is an invalid number\n",
                           sk_OPENSSL_STRING_value(osk, i));
                continue;
            }
            tmpbuf += j;
            tmplen -= j;
            atmp = at;
            ctmpbuf = tmpbuf;
            at = d2i_ASN1_TYPE(NULL, &ctmpbuf, tmplen);
            ASN1_TYPE_free(atmp);
            if (!at) {
                BIO_printf(bio_err, "Error parsing structure\n");
                ERR_print_errors(bio_err);
                goto end;
            }
            typ = ASN1_TYPE_get(at);
            if ((typ == V_ASN1_OBJECT)
                || (typ == V_ASN1_BOOLEAN)
                || (typ == V_ASN1_NULL)) {
                BIO_printf(bio_err, "Can't parse %s type\n", ASN1_tag2str(typ));
                ERR_print_errors(bio_err);
                goto end;
            }
            /* hmm... this is a little evil but it works */
            tmpbuf = at->value.asn1_string->data;
            tmplen = at->value.asn1_string->length;
        }
        str = tmpbuf;
        num = tmplen;
    }

    if (offset >= num) {
        BIO_printf(bio_err, "Error: offset too large\n");
        goto end;
    }

    num -= offset;

    if ((length == 0) || ((long)length > num))
        length = (unsigned int)num;
    if (derout) {
        if (BIO_write(derout, str + offset, length) != (int)length) {
            BIO_printf(bio_err, "Error writing output\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    if (!noout &&
        !ASN1_parse_dump(bio_out, &(str[offset]), length,
                         indent, dump)) {
        ERR_print_errors(bio_err);
        goto end;
    }
    ret = 0;
 end:
    BIO_free(derout);
    BIO_free(in);
    BIO_free(b64);
    if (ret != 0)
        ERR_print_errors(bio_err);
    BUF_MEM_free(buf);
    OPENSSL_free(name);
    OPENSSL_free(header);
    if (strictpem)
        OPENSSL_free(str);
    ASN1_TYPE_free(at);
    sk_OPENSSL_STRING_free(osk);
    return (ret);
}

static int do_generate(char *genstr, const char *genconf, BUF_MEM *buf)
{
    CONF *cnf = NULL;
    int len;
    unsigned char *p;
    ASN1_TYPE *atyp = NULL;

    if (genconf) {
        if ((cnf = app_load_config(genconf)) == NULL)
            goto err;
        if (!genstr)
            genstr = NCONF_get_string(cnf, "default", "asn1");
        if (!genstr) {
            BIO_printf(bio_err, "Can't find 'asn1' in '%s'\n", genconf);
            goto err;
        }
    }

    atyp = ASN1_generate_nconf(genstr, cnf);
    NCONF_free(cnf);
    cnf = NULL;

    if (!atyp)
        return -1;

    len = i2d_ASN1_TYPE(atyp, NULL);

    if (len <= 0)
        goto err;

    if (!BUF_MEM_grow(buf, len))
        goto err;

    p = (unsigned char *)buf->data;

    i2d_ASN1_TYPE(atyp, &p);

    ASN1_TYPE_free(atyp);
    return len;

 err:
    NCONF_free(cnf);
    ASN1_TYPE_free(atyp);
    return -1;
}

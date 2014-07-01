/* fsw_strfunc.h generated by mk_fsw_strfunc.py */

static int fsw_streq_ISO88591_UTF8(void *s1data, void *s2data, int len)
{
    int i;
    fsw_u8 *p1 = (fsw_u8 *)s1data;
    fsw_u8 *p2 = (fsw_u8 *)s2data;
    fsw_u32 c1, c2;
    
    for (i = 0; i < len; i++) {
        c1 = *p1++;
        c2 = *p2++;
        if ((c2 & 0xe0) == 0xc0) {
            c2 = ((c2 & 0x1f) << 6) | (*p2++ & 0x3f);
        } else if ((c2 & 0xf0) == 0xe0) {
            c2 = ((c2 & 0x0f) << 12) | ((*p2++ & 0x3f) << 6);
            c2 |= (*p2++ & 0x3f);
        } else if ((c2 & 0xf8) == 0xf0) {
            c2 = ((c2 & 0x07) << 18) | ((*p2++ & 0x3f) << 12);
            c2 |= ((*p2++ & 0x3f) << 6);
            c2 |= (*p2++ & 0x3f);
        }
        if (c1 != c2)
            return 0;
    }
    return 1;
}

#ifdef __MAKEWITH_TIANO
static int fsw_streq_ISO88591_UTF16(void *s1data, void *s2data, int len)
{
    int i;
    fsw_u8 *p1 = (fsw_u8 *)s1data;
    fsw_u16 *p2 = (fsw_u16 *)s2data;
    fsw_u32 c1, c2;
    
    for (i = 0; i < len; i++) {
        c1 = *p1++;
        c2 = *p2++;
        if (c1 != c2)
            return 0;
    }
    return 1;
}
#endif

static int fsw_streq_ISO88591_UTF16_SWAPPED(void *s1data, void *s2data, int len)
{
    int i;
    fsw_u8 *p1 = (fsw_u8 *)s1data;
    fsw_u16 *p2 = (fsw_u16 *)s2data;
    fsw_u32 c1, c2;
    
    for (i = 0; i < len; i++) {
        c1 = *p1++;
        c2 = *p2++; c2 = FSW_SWAPVALUE_U16(c2);
        if (c1 != c2)
            return 0;
    }
    return 1;
}

static int fsw_streq_UTF8_UTF16(void *s1data, void *s2data, int len)
{
    int i;
    fsw_u8 *p1 = (fsw_u8 *)s1data;
    fsw_u16 *p2 = (fsw_u16 *)s2data;
    fsw_u32 c1, c2;
    
    for (i = 0; i < len; i++) {
        c1 = *p1++;
        if ((c1 & 0xe0) == 0xc0) {
            c1 = ((c1 & 0x1f) << 6) | (*p1++ & 0x3f);
        } else if ((c1 & 0xf0) == 0xe0) {
            c1 = ((c1 & 0x0f) << 12) | ((*p1++ & 0x3f) << 6);
            c1 |= (*p1++ & 0x3f);
        } else if ((c1 & 0xf8) == 0xf0) {
            c1 = ((c1 & 0x07) << 18) | ((*p1++ & 0x3f) << 12);
            c1 |= ((*p1++ & 0x3f) << 6);
            c1 |= (*p1++ & 0x3f);
        }
        c2 = *p2++;
        if (c1 != c2)
            return 0;
    }
    return 1;
}

static int fsw_streq_UTF8_UTF16_SWAPPED(void *s1data, void *s2data, int len)
{
    int i;
    fsw_u8 *p1 = (fsw_u8 *)s1data;
    fsw_u16 *p2 = (fsw_u16 *)s2data;
    fsw_u32 c1, c2;
    
    for (i = 0; i < len; i++) {
        c1 = *p1++;
        if ((c1 & 0xe0) == 0xc0) {
            c1 = ((c1 & 0x1f) << 6) | (*p1++ & 0x3f);
        } else if ((c1 & 0xf0) == 0xe0) {
            c1 = ((c1 & 0x0f) << 12) | ((*p1++ & 0x3f) << 6);
            c1 |= (*p1++ & 0x3f);
        } else if ((c1 & 0xf8) == 0xf0) {
            c1 = ((c1 & 0x07) << 18) | ((*p1++ & 0x3f) << 12);
            c1 |= ((*p1++ & 0x3f) << 6);
            c1 |= (*p1++ & 0x3f);
        }
        c2 = *p2++; c2 = FSW_SWAPVALUE_U16(c2);
        if (c1 != c2)
            return 0;
    }
    return 1;
}

static int fsw_streq_UTF16_UTF16_SWAPPED(void *s1data, void *s2data, int len)
{
    int i;
    fsw_u16 *p1 = (fsw_u16 *)s1data;
    fsw_u16 *p2 = (fsw_u16 *)s2data;
    fsw_u32 c1, c2;
    
    for (i = 0; i < len; i++) {
        c1 = *p1++;
        c2 = *p2++; c2 = FSW_SWAPVALUE_U16(c2);
        if (c1 != c2)
            return 0;
    }
    return 1;
}

static fsw_status_t fsw_strcoerce_UTF8_ISO88591(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i;
    fsw_u8       *sp;
    fsw_u8       *dp;
    fsw_u32         c;
    
    dest->type = FSW_STRING_TYPE_ISO88591;
    dest->len  = srclen;
    dest->size = srclen * sizeof(fsw_u8);
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u8 *)srcdata;
    dp = (fsw_u8 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        if ((c & 0xe0) == 0xc0) {
            c = ((c & 0x1f) << 6) | (*sp++ & 0x3f);
        } else if ((c & 0xf0) == 0xe0) {
            c = ((c & 0x0f) << 12) | ((*sp++ & 0x3f) << 6);
            c |= (*sp++ & 0x3f);
        } else if ((c & 0xf8) == 0xf0) {
            c = ((c & 0x07) << 18) | ((*sp++ & 0x3f) << 12);
            c |= ((*sp++ & 0x3f) << 6);
            c |= (*sp++ & 0x3f);
        }
        *dp++ = (fsw_u8)c;
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_UTF16_ISO88591(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i;
    fsw_u16       *sp;
    fsw_u8       *dp;
    fsw_u32         c;
    
    dest->type = FSW_STRING_TYPE_ISO88591;
    dest->len  = srclen;
    dest->size = srclen * sizeof(fsw_u8);
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u16 *)srcdata;
    dp = (fsw_u8 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        *dp++ = (fsw_u8)c;
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_UTF16_SWAPPED_ISO88591(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i;
    fsw_u16       *sp;
    fsw_u8       *dp;
    fsw_u32         c;
    
    dest->type = FSW_STRING_TYPE_ISO88591;
    dest->len  = srclen;
    dest->size = srclen * sizeof(fsw_u8);
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u16 *)srcdata;
    dp = (fsw_u8 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++; c = FSW_SWAPVALUE_U16(c);
        *dp++ = (fsw_u8)c;
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_ISO88591_UTF16(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i;
    fsw_u8       *sp;
    fsw_u16       *dp;
    fsw_u32         c;
    
    dest->type = FSW_STRING_TYPE_UTF16;
    dest->len  = srclen;
    dest->size = srclen * sizeof(fsw_u16);
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u8 *)srcdata;
    dp = (fsw_u16 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        *dp++ = (fsw_u16)c;
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_UTF8_UTF16(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i;
    fsw_u8       *sp;
    fsw_u16       *dp;
    fsw_u32         c;
    
    dest->type = FSW_STRING_TYPE_UTF16;
    dest->len  = srclen;
    dest->size = srclen * sizeof(fsw_u16);
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u8 *)srcdata;
    dp = (fsw_u16 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        if ((c & 0xe0) == 0xc0) {
            c = ((c & 0x1f) << 6) | (*sp++ & 0x3f);
        } else if ((c & 0xf0) == 0xe0) {
            c = ((c & 0x0f) << 12) | ((*sp++ & 0x3f) << 6);
            c |= (*sp++ & 0x3f);
        } else if ((c & 0xf8) == 0xf0) {
            c = ((c & 0x07) << 18) | ((*sp++ & 0x3f) << 12);
            c |= ((*sp++ & 0x3f) << 6);
            c |= (*sp++ & 0x3f);
        }
        *dp++ = (fsw_u16)c;
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_UTF16_SWAPPED_UTF16(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i;
    fsw_u16       *sp;
    fsw_u16       *dp;
    fsw_u32         c;
    
    dest->type = FSW_STRING_TYPE_UTF16;
    dest->len  = srclen;
    dest->size = srclen * sizeof(fsw_u16);
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u16 *)srcdata;
    dp = (fsw_u16 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++; c = FSW_SWAPVALUE_U16(c);
        *dp++ = (fsw_u16)c;
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_ISO88591_UTF8(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i, destsize;
    fsw_u8       *sp;
    fsw_u8       *dp;
    fsw_u32         c;
    
    sp = (fsw_u8 *)srcdata;
    destsize = 0;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        
        if (c < 0x000080)
            destsize++;
        else if (c < 0x000800)
            destsize += 2;
        else if (c < 0x010000)
            destsize += 3;
        else
            destsize += 4;
    }
    
    dest->type = FSW_STRING_TYPE_UTF8;
    dest->len  = srclen;
    dest->size = destsize;
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u8 *)srcdata;
    dp = (fsw_u8 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        
        if (c < 0x000080) {
            *dp++ = (fsw_u8)c;
        } else if (c < 0x000800) {
            *dp++ = (fsw_u8)(0xc0 | ((c >> 6) & 0x1f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        } else if (c < 0x010000) {
            *dp++ = (fsw_u8)(0xe0 | ((c >> 12) & 0x0f));
            *dp++ = (fsw_u8)(0x80 | ((c >> 6) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        } else {
            *dp++ = (fsw_u8)(0xf0 | ((c >> 18) & 0x07));
            *dp++ = (fsw_u8)(0x80 | ((c >> 12) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | ((c >> 6) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        }
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_UTF16_UTF8(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i, destsize;
    fsw_u16       *sp;
    fsw_u8       *dp;
    fsw_u32         c;
    
    sp = (fsw_u16 *)srcdata;
    destsize = 0;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        
        if (c < 0x000080)
            destsize++;
        else if (c < 0x000800)
            destsize += 2;
        else if (c < 0x010000)
            destsize += 3;
        else
            destsize += 4;
    }
    
    dest->type = FSW_STRING_TYPE_UTF8;
    dest->len  = srclen;
    dest->size = destsize;
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u16 *)srcdata;
    dp = (fsw_u8 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++;
        
        if (c < 0x000080) {
            *dp++ = (fsw_u8)c;
        } else if (c < 0x000800) {
            *dp++ = (fsw_u8)(0xc0 | ((c >> 6) & 0x1f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        } else if (c < 0x010000) {
            *dp++ = (fsw_u8)(0xe0 | ((c >> 12) & 0x0f));
            *dp++ = (fsw_u8)(0x80 | ((c >> 6) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        } else {
            *dp++ = (fsw_u8)(0xf0 | ((c >> 18) & 0x07));
            *dp++ = (fsw_u8)(0x80 | ((c >> 12) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | ((c >> 6) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        }
    }
    return FSW_SUCCESS;
}

static fsw_status_t fsw_strcoerce_UTF16_SWAPPED_UTF8(void *srcdata, int srclen, struct fsw_string *dest)
{
    fsw_status_t    status;
    int             i, destsize;
    fsw_u16       *sp;
    fsw_u8       *dp;
    fsw_u32         c;
    
    sp = (fsw_u16 *)srcdata;
    destsize = 0;
    for (i = 0; i < srclen; i++) {
        c = *sp++; c = FSW_SWAPVALUE_U16(c);
        
        if (c < 0x000080)
            destsize++;
        else if (c < 0x000800)
            destsize += 2;
        else if (c < 0x010000)
            destsize += 3;
        else
            destsize += 4;
    }
    
    dest->type = FSW_STRING_TYPE_UTF8;
    dest->len  = srclen;
    dest->size = destsize;
    status = fsw_alloc(dest->size, &dest->data);
    if (status)
        return status;
    
    sp = (fsw_u16 *)srcdata;
    dp = (fsw_u8 *)dest->data;
    for (i = 0; i < srclen; i++) {
        c = *sp++; c = FSW_SWAPVALUE_U16(c);
        
        if (c < 0x000080) {
            *dp++ = (fsw_u8)c;
        } else if (c < 0x000800) {
            *dp++ = (fsw_u8)(0xc0 | ((c >> 6) & 0x1f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        } else if (c < 0x010000) {
            *dp++ = (fsw_u8)(0xe0 | ((c >> 12) & 0x0f));
            *dp++ = (fsw_u8)(0x80 | ((c >> 6) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        } else {
            *dp++ = (fsw_u8)(0xf0 | ((c >> 18) & 0x07));
            *dp++ = (fsw_u8)(0x80 | ((c >> 12) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | ((c >> 6) & 0x3f));
            *dp++ = (fsw_u8)(0x80 | (c & 0x3f));
        }
    }
    return FSW_SUCCESS;
}

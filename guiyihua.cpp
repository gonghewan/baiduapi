#include <string>
#include <string.h>
#include <iconv.h>

int code_convert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) <= 0) return -1;
	iconv_close(cd);
	return 0;
}
int GbkToUtf8(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}
int Utf8ToGbk(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}
    
static inline void delspace(const std::string &oriStr, std::string &outStr){
    outStr = "";
    for (size_t i = 0; i < oriStr.length(); ++i){
        char tmp = oriStr[i];
        outStr += tmp;
        if (tmp == ' '){
            for(;i < oriStr.length() && oriStr[i]==' ';++i){}
            outStr += oriStr[i];
        }
    }
}
static inline void toDBS(std::string &oriStr, std::string &dstStr){
    dstStr = "";
    char result_g[10240];
    Utf8ToGbk((char*)oriStr.c_str(), strlen(oriStr.c_str()), result_g, 10240);
    std::string str_gbk(result_g);
    std::string str_gbk_format = "";
    for (unsigned int i = 0; i < str_gbk.length(); i++) {
        unsigned char tmp = str_gbk[i];
        unsigned char tmp1 = str_gbk[i + 1];
        if(tmp == 163){
            ++i;
            str_gbk_format += (unsigned char)tmp1-128;
        }else{
            str_gbk_format += tmp;
        }
    }
    char result_u[10240];
    GbkToUtf8((char*)str_gbk_format.c_str(), strlen(str_gbk_format.c_str()), result_u, 10240);
    delspace(result_u, dstStr);
}
int main(){
    std::string re_name = "555(柔和：，；低焦油 白)";
    std::string res = ""; // result
    toDBS(re_name, res);
}

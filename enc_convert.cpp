#include<iconv.h>
#include <string.h>
#include <string>

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
int main(){
  std::string oriStr = "asd";
  char result_g[10240];
  Utf8ToGbk((char*)oriStr.c_str(), strlen(oriStr.c_str()), result_g, 10240);
  std::string str_gbk_format(result_g);
  // do something else
  // ...
  char result_u[10240];
  GbkToUtf8((char*)str_gbk_format.c_str(), strlen(str_gbk_format.c_str()), result_u, 10240);
}

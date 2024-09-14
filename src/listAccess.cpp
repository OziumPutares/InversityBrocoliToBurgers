#include "listAccess.hpp"
//////Using Code provided by stackoverflow post
/// https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c
void GetPage(char const *url, char const *file_name) {
  CURL *Easyhandle = curl_easy_init();

  curl_easy_setopt(Easyhandle, CURLOPT_URL, url);

  FILE *File = fopen(file_name, "w");

  curl_easy_setopt(Easyhandle, CURLOPT_WRITEDATA, File);

  curl_easy_perform(Easyhandle);

  curl_easy_cleanup(Easyhandle);

  fclose(File);
}

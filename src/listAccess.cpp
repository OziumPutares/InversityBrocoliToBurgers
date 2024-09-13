#include "listAccess.hpp"
//////Using Code provided by stackoverflow post
/// https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c

// all of your legacy C code here
void get_page(std::string url, const char *file_name) {
  CURL *easyhandle = curl_easy_init();

  curl_easy_setopt(easyhandle, CURLOPT_URL, url.cbegin());

  FILE *file = fopen(file_name, "w");

  curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file);

  curl_easy_perform(easyhandle);

  curl_easy_cleanup(easyhandle);

  fclose(file);
}

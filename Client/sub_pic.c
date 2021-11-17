#include <stdio.h>
#include <curl/curl.h>

int sub_pic(char sub_text[100])
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char text[100] ;
    char *url = "sftp://admin:U%25%25FSM74Y%24GZ@203.146.252.179:22/~/web/sv1.kjpie/public_html/uploads/";
    char outfilename[100];
    curl = curl_easy_init();
    sprintf(text,"%s%s.jpg",url,sub_text);
    sprintf(outfilename,"sub_img/%s.jpg",sub_text);

    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, text);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if(res == CURLE_OK)
            printf("Download Successful\n");
        else
            printf("ERROR: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        fclose(fp);

        FILE *fpd;
        fpd = fopen("data.txt","a");
        fprintf(fpd,"%s\n",sub_text);
        fclose(fpd);
    }
    return 0;
}

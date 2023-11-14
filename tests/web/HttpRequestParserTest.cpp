#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include "../../src/web/helpers/HttpRequestParser.hpp"

TEST(ParserEmptyTest, CheckParserResult){
    const std::string request = "";

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);
    
    EXPECT_EQ(result.GetMethod(), web_layout::Method::GET);
    EXPECT_EQ(result.GetPath(), "");
    EXPECT_EQ(result.GetBody(), "");
}

TEST(ParserTest, CheckParserResult) {
    const std::string request = 
        "GET /id/2 HTTP/1.1\n \
        Host: developer.mozilla.org\n \
        Accept-Language: fr";
    
    std::unordered_map<std::string,std::string> headers;
    headers.emplace("Host","developer.mozilla.org");
    headers.emplace("Accept-Language", "fr");

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::GET);
    EXPECT_EQ(result.GetPath(), "/id/2");
    EXPECT_EQ(result.GetHeaders(), headers);
    EXPECT_EQ(result.GetBody(), "");
}

TEST(ParserTestWithBody, CheckParserResult) {
    const std::string request = 
        "POST /cgi-bin HTTP/1.1\n\
        Host: www.tutorialspoint.com\n\
        \n\
        licenseID=string&content=string&/paramsXML=string";

    std::unordered_map<std::string,std::string> headers;
    headers.emplace("Host", "www.tutorialspoint.com");

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::POST);
    EXPECT_EQ(result.GetPath(), "/cgi-bin");
    EXPECT_EQ(result.GetHeaders(), headers);
    EXPECT_EQ(result.GetBody(), "licenseID=string&content=string&/paramsXML=string");
}

TEST(ParserTestWithoutHeaders, CheckParserResult) {
    const std::string request = 
        "PUT /main HTTP/1.1\n\
        \n\
        licenseID=string&content=string&/paramsXML=string";

    std::unordered_map<std::string,std::string> headers;

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::PUT);
    EXPECT_EQ(result.GetPath(), "/main");
    EXPECT_EQ(result.GetHeaders(), headers);
    EXPECT_EQ(result.GetBody(), "licenseID=string&content=string&/paramsXML=string");
}

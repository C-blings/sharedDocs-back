#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <web/helpers/HttpRequestParser.hpp>

TEST(ParserTest, CheckParserResult) {
    const std::string request = 
        "GET /id/2 HTTP/1.1\n\r \
        Host: developer.mozilla.org\n\r \
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

TEST(ParserTest, CheckSingleParameter) {
    const std::string request =
            "GET /id/2?user=userName HTTP/1.1\n\r \
        Host: developer.mozilla.org\n\r \
        Accept-Language: fr";

    std::unordered_map<std::string,std::string> parameters;
    parameters.emplace("user", "userName");

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::GET);
    EXPECT_EQ(result.GetPath(), "/id/2");
    EXPECT_EQ(result.GetParameters(), parameters);
}

TEST(ParserTest, CheckMultipleParameter) {
    const std::string request =
            "GET /id/2?user=userName;nickname=nickName HTTP/1.1\n\r \
        Host: developer.mozilla.org\n\r \
        Accept-Language: fr";

    std::unordered_map<std::string,std::string> parameters;
    parameters.emplace("user", "userName");
    parameters.emplace("nickname", "nickName");

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::GET);
    EXPECT_EQ(result.GetPath(), "/id/2");
    EXPECT_EQ(result.GetParameters(), parameters);
}

TEST(ParserTestWithBody, CheckParserResult) {
    const std::string request = 
        "POST /cgi-bin HTTP/1.1\n\r \
        Host: www.tutorialspoint.com\n\r \
        \n\r \
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
        "PUT /main HTTP/1.1\n\r \
        \n\r \
        licenseID=string&content=string&/paramsXML=string";

    std::unordered_map<std::string,std::string> headers;

    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::PUT);
    EXPECT_EQ(result.GetPath(), "/main");
    EXPECT_EQ(result.GetHeaders(), headers);
    EXPECT_EQ(result.GetBody(), "licenseID=string&content=string&/paramsXML=string");
}

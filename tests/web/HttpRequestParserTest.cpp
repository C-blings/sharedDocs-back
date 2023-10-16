#include <gtest/gtest.h>
#include "../../src/web/helpers/HttpRequestParser.hpp"

TEST(ParserTest, CheckParserResult){
    const std::string request = "";
    web_layout::HttpRequest result = web_layout::HttpRequestParser::GetHttpRequest(request);

    EXPECT_EQ(result.GetMethod(), web_layout::Method::GET);
    EXPECT_EQ(result.GetPath(), "");
}

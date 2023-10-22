#pragma once

#include "../models/HttpRequest.hpp"
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace web_layout{

    class HttpRequestParser{
        public:
            
            static HttpRequest GetHttpRequest(const std::string& request){
                std::vector<std::string> request_lines;
                boost::split(request_lines, request, boost::is_any_of("\n\r"), boost::token_compress_on);
				
				std::vector<std::string> methodAndPath;
				boost::split(methodAndPath, request_lines[0], boost::is_any_of(" "), boost::token_compress_on);

				Method method;
				if(methodAndPath[0] == "GET") {
						method = Method::GET;
				} else {
						method = Method::POST;
				}

				std::string path = methodAndPath[1];
				std::string headers;
				std::string body;

				int i;
				for(i = 1; i < request_lines.size(); ++i) {
						if(request_lines[i] == "") {
								++i;
								break;
						}
						headers += request_lines[i] + '\n';
				}

				for(; i < request_lines.size(); ++i) {
						body += request_lines[i] + '\n';
				}

                return HttpRequest(method, path, headers, body);
            }
    };

}

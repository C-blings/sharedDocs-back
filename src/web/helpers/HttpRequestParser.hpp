#pragma once

#include "../models/HttpRequest.hpp"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

namespace web_layout{

    class HttpRequestParser{
        public:
            
            static HttpRequest GetHttpRequest(const std::string& request){
                std::vector<std::string> request_lines;
                boost::split(request_lines, request, boost::is_any_of("\n\r"), boost::token_compress_on);
				
				std::vector<std::string> method_and_path;
				boost::split(method_and_path, request_lines[0], boost::is_any_of(" "), boost::token_compress_on);

				Method method;
				if(method_and_path[0] == "GET") {
						method = Method::GET;
				} else if(method_and_path[0] == "POST") {
						method = Method::POST;
				} else if(method_and_path[0] == "PUT") {
						method = Method::PUT;
				} else if(method_and_path[0] == "DELETE") {
						method = Method::DELETE;
				}

				std::string path = method_and_path[1];
				std::unordered_map<std::string, std::string> headers;
				std::string body;

				int i;
				for(i = 1; i < request_lines.size(); ++i) {
						if(request_lines[i] == "") {
								++i;
								break;
						}
						std::vector<std::string> header;
						boost::split(header, request_lines[i], boost::is_any_of(": "), boost::token_compress_on);
						headers[header[0]] = header[1];
				}

				for(; i < request_lines.size(); ++i) {
						body += request_lines[i] + '\n';
				}

                return HttpRequest(method, path, headers, body);
            }
    };

}

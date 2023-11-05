#pragma once

#include "../models/HttpRequest.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

namespace web_layout{

    class HttpRequestParser{
        private:
            static inline std::unordered_map<std::string, Method> string_to_method = {
                {"GET", Method::GET},
                {"POST", Method::POST},
                {"PUT", Method::PUT},
                {"DELETE", Method::DELETE},
                {"OPTIONS", Method::OPTIONS},
            };
        public:
            static HttpRequest GetHttpRequest(const std::string& request){
                std::vector<std::string> request_lines;
                boost::split(request_lines, request, boost::is_any_of("\n\r"), boost::token_compress_on);
				
				std::vector<std::string> method_and_path;
				boost::split(method_and_path, request_lines[0], boost::is_any_of(" "), boost::token_compress_on);

				Method method = string_to_method[method_and_path[0]];
				std::string path = method_and_path[1];
				std::unordered_map<std::string, std::string> headers;
				std::string body;

				int i;
				for(i = 1; i < request_lines.size(); ++i) {
						std::vector<std::string> header;
						boost::split(header, request_lines[i], boost::is_any_of(": "), boost::token_compress_on);
                        if (header.size() == 2){
                            headers.emplace(header[0], header[1]);
                        }else{
                            ++i;
                            break;
                        }
				}

				for(; i < request_lines.size(); ++i) {
						body += request_lines[i] + '\n';
				}

                return HttpRequest(method, path, headers, body);
            }
    };

}

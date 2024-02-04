#include <crow/settings.h>
#include <crow/app.h>
#include "config.hpp"
#include "link.hpp"
#include "log.hpp"
#include <crow.h>
#include <random>

std::string join_url(std::string url) {
  if(envurl[envurl.length()-1] == '/')
    return envurl+url;
  return envurl+"/"+url;
}

int main(){
  crow::SimpleApp app;
  app.loglevel(crow::LogLevel::Warning);
  if(!envsave){
    info("NOSAVE is set, not loading any saved links");
    goto SKIP_LOAD;
  }

  if(!load_links())
    info("No saved links, loading an empty list");
  
SKIP_LOAD:
  CROW_ROUTE(app, "/add")([](const crow::request& req, crow::response& res){
    char* url = req.url_params.get("url");

    if(nullptr == url) {
      res.code = 400;
      res.write("Provide a URL and a password");
      return res.end();
    }

    std::string urlstr(url);
    if(urlstr.length() > 7500) {
      res.code = 400;
      res.write("URL is too large");
      return res.end();
    }
    
    if(urlstr.rfind("http://", 0) != 0 && urlstr.rfind("https://", 0) != 0){
      res.code = 400;
      res.write("Bad URL");
      return res.end();
    }

    std::string newurl = add_url(urlstr);
    res.write(join_url(newurl));
    return res.end();
  });
  
  CROW_ROUTE(app, "/")([](const crow::request&, crow::response& res){      
    res.redirect("/static/index.html");
    return res.end();
  });

  CROW_ROUTE(app, "/<string>")([](const crow::request&, crow::response& res, std::string url){
    if(url.empty()){
      res.redirect("/static/index.html");
      return res.end();
    }
        
    if(url.compare("add")==0 || url.compare("favicon.ico")==0)
      return res.end();

    std::string org = find_url(url);
    if(org.empty()) {
      res.set_static_file_info("./static/error.html");
      return res.end();
    } 

    res.write("redirecting...");
    res.redirect(org);
    return res.end();
  });

  app.port(8080).run();
}

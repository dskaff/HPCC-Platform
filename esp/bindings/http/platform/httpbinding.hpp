/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2012 HPCC Systems®.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
############################################################################## */

#ifndef _HTTPBINDING_HPP__
#define _HTTPBINDING_HPP__

#include "http/platform/httptransport.ipp"
#include "espcache.hpp"

#include "bindutil.hpp"
#include "seclib.hpp"

class CMethodInfo : public CInterface
{
public:
    StringAttr m_label;
    StringAttr m_requestLabel;
    StringAttr m_responseLabel;

    //StringBuffer m_securityTag;
    //StringBuffer m_optionalTag;
    //double       m_minVer;
    //double       m_maxVer;

public:
    CMethodInfo(const char * label, const char * req, const char * resp) //, const char *sectag, const char *optag,const char* minver=NULL, const char* maxver=NULL)
    {
        m_label.set(label);
        m_requestLabel.set(req);
        m_responseLabel.set(resp);
        /*
        if (sectag)
            m_securityTag.append(sectag);
        if (optag)
            m_optionalTag.append(optag);
        m_minVer = (minver)?atof(minver):-1;
        m_maxVer = (maxver)?atof(maxver):-1;
        */
    };

    CMethodInfo(CMethodInfo &src)
    {
        m_label.set(src.m_label);
        m_requestLabel.set(src.m_requestLabel);
        m_responseLabel.set(src.m_responseLabel);
    };
};

typedef CIArrayOf<CMethodInfo> MethodInfoArray;

interface IEspHttpBinding
{
    virtual void handleHttpPost(CHttpRequest *request, CHttpResponse *response)=0;

    virtual int onGet(CHttpRequest* request, CHttpResponse* response) = 0;
    virtual int onPost(CHttpRequest* request, CHttpResponse* response) = 0;
    virtual int onSoapRequest(CHttpRequest* request, CHttpResponse* response) = 0;
    virtual int onPostForm(CHttpRequest* request, CHttpResponse* response) = 0;

    virtual int onGetNotFound(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *serv)=0;
    virtual int onGetRoot(IEspContext &context, CHttpRequest* request,  CHttpResponse* response)=0;
    virtual int onGetIndex(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *servName)=0;
    virtual int onGetStaticIndex(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *servName)=0;
    virtual int onGetService(IEspContext &context, CHttpRequest* request,   CHttpResponse* response, const char *servName, const char *methodName, const char *pathex)=0;
    virtual int onGetForm(IEspContext &context, CHttpRequest* request,   CHttpResponse* response, const char *servName, const char *methodName)=0;
    virtual int onGetXForm(IEspContext &context, CHttpRequest* request,   CHttpResponse* response, const char *servName, const char *methodName)=0;
    virtual int onGetInstantQuery(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName)=0;
    virtual int onFeaturesAuthorize(IEspContext &context, MapStringTo<SecAccessFlags> & pmap, const char *serviceName, const char *methodName)=0;

    virtual int onGetQuery(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *servName, const char *methodName)=0;
    virtual int onGetResult(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *servName, const char *methodName, const char *resultPath)=0;
    virtual int onGetResultPresentation(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName, StringBuffer &xmlResult)=0;
    virtual int onGetFile(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *path)=0;
    virtual int onGetContent(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName)=0;
    virtual int onGetWsdl(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName)=0;
    virtual int onGetXsd(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName)=0;
    virtual int onGetSoapBuilder(IEspContext &context, CHttpRequest* request, CHttpResponse* response,  const char *serv, const char *method)=0;
    virtual int onGetReqSampleXml(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method)=0;
    virtual int onGetRespSampleXml(IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method)=0;
    virtual int onGetRespSampleJson(IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method)=0;
    virtual int onGetReqSampleJson(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method)=0;
    virtual int onStartUpload(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method)=0;
    virtual int onFinishUpload(IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method,
    StringArray& fileNames, StringArray& files, IMultiException *me)=0;
};

typedef MapStringTo<int> wsdlIncludedTable;

interface IEspWsdlSections
{
    virtual StringBuffer & getServiceName(StringBuffer & resp)=0;
    virtual bool isValidServiceName(IEspContext &context, const char *name)=0;
    virtual bool qualifyServiceName(IEspContext &context, const char *servname, const char *methname, StringBuffer &servQName, StringBuffer *methQName)=0;

//  virtual MethodInfoArray & queryQualifiedNames(IEspContext& ctx)=0;
    virtual int getQualifiedNames(IEspContext& ctx, MethodInfoArray & methods)=0;
    virtual int getXsdDefinition(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda)=0;
    virtual int getWsdlMessages(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda)=0;
    virtual int getWsdlPorts(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda)=0;
    virtual int getWsdlBindings(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda)=0;
};

class esp_http_decl EspHttpBinding :
    implements IEspHttpBinding,
    implements IEspWsdlSections
{
private:
    StringAttr              m_host;
    StringAttr              m_realm;
    unsigned short          m_port;
    bool                    m_viewConfig;
    bool                    m_formOptions;
    StringAttr              m_configFile;
    double                  m_wsdlVer;

    HINSTANCE               m_hSecDll;

    StringAttr              m_authtype;
    StringAttr              m_authmethod;
    StringBuffer            m_reqPath;
    StringBuffer            m_filespath;
    StringBuffer            m_wsdlAddress;
    Owned<ISecManager>      m_secmgr;
    Owned<IAuthMap>         m_authmap;
    Owned<IAuthMap>         m_feature_authmap;
    Owned<IAuthMap>         m_setting_authmap;
    Owned<IPTree>           m_subservices;

    StringAttrMapping desc_map;
    StringAttrMapping help_map;

    Owned<IEspCache> espCacheClient;
    StringAttr espCacheInitString;
    unsigned cacheMethods = 0;
    MapStringTo<unsigned> cacheSecondsMap;
    MapStringTo<bool> cacheGlobalMap;

    bool queryCacheSeconds(const char *method, unsigned& cacheSecond);
    bool queryCacheGlobal(const char *method);
    const char* createESPCacheID(CHttpRequest* request, StringBuffer& cacheID);
    void addToESPCache(CHttpRequest* request, CHttpResponse* response, const char* cacheID);
    bool sendFromESPCache(CHttpRequest* request, CHttpResponse* response, const char* cacheID);

    StringAttr              processName;
    StringAttr              domainName;
    StringBuffer            sessionSDSPath;
    StringBuffer            espSessionSDSPath;
    StringBuffer            sessionIDCookieName;
    AuthType                domainAuthType;

    StringAttr              loginURL;
    StringAttr              logoutURL;
    int                     sessionTimeoutSeconds = ESP_SESSION_TIMEOUT; //-1: never
    int                     checkSessionTimeoutSeconds = ESP_CHECK_SESSION_TIMEOUT;
    BoolHash                domainAuthResources;
    StringArray             domainAuthResourcesWildMatch;

    void getXMLMessageTag(IEspContext& ctx, bool isRequest, const char *method, StringBuffer& tag);

protected:
    MethodInfoArray m_methods;
    bool                    m_includeSoapTest;
    StringBuffer            m_challenge_realm;
    StringAttr              m_defaultSvcVersion;

public:
    EspHttpBinding(IPropertyTree* cfg, const char *bindname=NULL, const char *procname=NULL);

    void getDefaultNavData(IPropertyTree & data);


    virtual StringBuffer &getBaseFilePath(StringBuffer &path){return path.append(m_filespath);}
    const char *getHost(){return m_host.str();}
    unsigned short getPort(){return m_port;}

    void setRealm(const char *realm){m_realm.set((realm) ? realm : "EspService");}
    const char *getRealm(){return m_realm.str();}
    const char* getChallengeRealm() {return m_challenge_realm.str();}
    double getWsdlVersion(){return m_wsdlVer;}
    void setWsdlVersion(double ver){m_wsdlVer=ver;}
    const char *getWsdlAddress(){return m_wsdlAddress.str();}
    void setWsdlAddress(const char *wsdladdress){m_wsdlAddress.set(wsdladdress);}

    virtual void setRequestPath(const char *path);
    virtual bool rootAuthRequired();
    virtual bool authRequired(CHttpRequest *request);
    virtual bool doAuth(IEspContext* ctx);
    virtual void populateRequest(CHttpRequest *request);
    virtual void getNavSettings(int &width, bool &resizable, bool &scroll){width=165;resizable=false;scroll=true;}
    virtual const char* getRootPage(IEspContext* ctx) {return NULL;}

    virtual StringBuffer &generateNamespace(IEspContext &context, CHttpRequest* request, const char *serv, const char *method, StringBuffer &ns);
    virtual void getSchemaLocation(IEspContext &context, CHttpRequest* request, StringBuffer &schemaLocation );

    virtual StringBuffer &getRequestPath(){return m_reqPath;}
    static int formatHtmlResultSet(IEspContext &context, const char *serv, const char *method, const char *resultsXml, StringBuffer &html);
    int formatResultsPage(IEspContext &context, const char *serv, const char *method, StringBuffer &results, StringBuffer &page);

    virtual bool supportGeneratedForms(){return true;}

    int onGetException(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, IException &e);

    void addMethodDescription(const char *method, const char *description)
    {
        StringBuffer key(method);
        desc_map.setValue(key.toUpperCase().str(), description);
    }
    void addMethodHelp(const char *method, const char *help)
    {
        StringBuffer key(method);
        help_map.setValue(key.toUpperCase().str(), help);
    }
    //The setCacheTimeout() is not thread safe because it is only called when ESP is
    //starting and the WsWorkunits lib is loading.
    void setCacheTimeout(const char *method, unsigned timeoutSeconds, bool global)
    {
        StringBuffer key(method);
        cacheSecondsMap.setValue(key.toUpperCase().str(), timeoutSeconds);
        cacheMethods++;
        if (global)
            cacheGlobalMap.setValue(key.str(), global);
    }

    int onGetConfig(IEspContext &context, CHttpRequest* request, CHttpResponse* response);

    virtual bool setContentFromFile(IEspContext &context, CHttpResponse &resp, const char *filepath);

//interface IEspHttpBinding:
    virtual void handleHttpPost(CHttpRequest *request, CHttpResponse *response);
    virtual int onGet(CHttpRequest* request, CHttpResponse* response);
    virtual int onGetWsdl(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName);
    virtual int onGetXsd(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serviceName, const char *methodName);

    virtual int onPost(CHttpRequest* request, CHttpResponse* response){return 0;};

    virtual int onGetNotFound(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *serv);
    virtual int onGetVersion(IEspContext &context, CHttpRequest* request, CHttpResponse* response,  const char *serv);
    virtual int onGetRoot(IEspContext &context, CHttpRequest* request,  CHttpResponse* response);
    virtual int onGetIndex(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *serv);
    virtual int onGetStaticIndex(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *serv);
    virtual int onGetForm(IEspContext &context, CHttpRequest* request,   CHttpResponse* response, const char *serv, const char *method);
    virtual int onGetXForm(IEspContext &context, CHttpRequest* request,   CHttpResponse* response, const char *serv, const char *method);
    virtual int onGetInstantQuery(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method);
    virtual int onFeaturesAuthorize(IEspContext &context, MapStringTo<SecAccessFlags> & pmap, const char *serviceName, const char *methodName);
    virtual int onGetResult(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method, const char *pathex);
    virtual int onGetResultPresentation(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method, StringBuffer &xmlResult);
    virtual int onGetFile(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *path);
    virtual int onGetItext(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *path);
    virtual int onGetIframe(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *path);
    virtual int onGetContent(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method);
    virtual int onGetSoapBuilder(IEspContext &context, CHttpRequest* request, CHttpResponse* response,  const char *serv, const char *method);

    virtual int onSoapRequest(CHttpRequest* request, CHttpResponse* response){return 0;}

    // In general, there is no difference between a query and an instant query;
    //   in some cases we may want to return the url for results from a query
    //   and the results themselves from an instant query.
    virtual int onGetQuery(IEspContext &context, CHttpRequest* request,  CHttpResponse* response, const char *serviceName, const char *methodName)
    {
        return onGetInstantQuery(context,request,response,serviceName,methodName);
    }

    virtual int onGetService(IEspContext &context, CHttpRequest* request,   CHttpResponse* response, const char *serv, const char *method, const char *pathex)
    {
        //when a service url is requested with no parameters, the default is to treat it as a query with no parameters
        return onGetQuery(context, request, response, serv, method);
    }

    virtual int onPostForm(CHttpRequest* request, CHttpResponse* response)
    {
        //default to treating a posted form just like an HTTP-GET request
        return onGet(request, response);
    }

    virtual int onGetReqSampleXml(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method);
    virtual int onGetRespSampleXml(IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method);
    virtual int onGetRespSampleJson(IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method);
    virtual int onGetReqSampleJson(IEspContext &ctx, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method);

    virtual int onStartUpload(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method);
    virtual int onFinishUpload(IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method,
        StringArray& fileNames, StringArray& files, IMultiException *me);

//interface IEspWsdlSections
    StringBuffer & getServiceName(StringBuffer & resp){return resp;}
    bool isValidServiceName(IEspContext &context, const char *name){return false;}
    bool qualifyServiceName(IEspContext &context, const char *servname, const char *methname, StringBuffer &servQName, StringBuffer *methQName){return false;}
    bool qualifySubServiceName(IEspContext &context, const char *servname, const char *methname, StringBuffer &servQName, StringBuffer *methQName);
    virtual bool qualifyMethodName(IEspContext &context, const char *methname, StringBuffer *methQName){return (!methname);}

//  MethodInfoArray &queryQualifiedNames(IEspContext& ctx) { m_methods.popAll(); getQualifiedNames(ctx,m_methods); return m_methods;};

    int getXsdDefinition(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda){return 0;};
    int getWsdlMessages(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda);
    int getWsdlPorts(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda);
    int getWsdlBindings(IEspContext &context, CHttpRequest *request, StringBuffer &content, const char *service, const char *method, bool mda);

    virtual int getMethodDescription(IEspContext &context, const char *serv, const char *method, StringBuffer &page);
    virtual int getMethodHelp(IEspContext &context, const char *serv, const char *method, StringBuffer &page);

    virtual int getMethodHtmlForm(IEspContext &context, CHttpRequest* request, const char *serv, const char *method, StringBuffer &page, bool bIncludeFormTag){return 0;}
    virtual bool hasSubService(IEspContext &context, const char *name);

    virtual IRpcRequestBinding *createReqBinding(IEspContext &context, IHttpMessage *ireq, const char *service, const char *method){return NULL;}

    bool isMethodInSubService(IEspContext &context, const char *servname, const char *methname)
    {
        if (m_subservices)
        {
            StringBuffer xpath;
            xpath.appendf("SubService[@name='%s']/SubServiceMethod[@name='%s']", servname, methname);
            return m_subservices->hasProp(xpath.str());
        }
        return false;
    }
    ISecManager* querySecManager() const { return m_secmgr.get(); }
    IAuthMap* queryAuthMAP() const { return m_authmap.get();}
    const char* queryAuthMethod() const { return m_authmethod.str(); }
    void setProcessName(const char* name) { processName.set(name); }
    const char* queryProcessName() const { return processName.get(); }
    void setDomainName(const char* name) { domainName.set(name ? name : "default"); }
    const char* queryDomainName() const { return domainName.get(); }
    void setSessionSDSPath(const char* path) { sessionSDSPath.set(path); }
    const char* querySessionSDSPath() const { return sessionSDSPath.str(); }
    void setESPSessionSDSPath(const char* path) { espSessionSDSPath.set(path); }
    const char* queryESPSessionSDSPath() const { return espSessionSDSPath.str(); }
    const char* querySessionIDCookieName() const { return sessionIDCookieName.str(); }
    AuthType getDomainAuthType() const { return domainAuthType; }
    const char* queryLoginURL() const { return loginURL.get(); }
    const char* queryLogoutURL() const { return logoutURL.get(); }
    int getSessionTimeoutSeconds() const { return sessionTimeoutSeconds; }
    int getCheckSessionTimeoutSeconds() const { return checkSessionTimeoutSeconds; }
    bool isDomainAuthResources(const char* resource)
    {
        bool* found = domainAuthResources.getValue(resource);
        if (found && *found)
            return true;

        ForEachItemIn(i, domainAuthResourcesWildMatch)
        {
            const char* wildResourcePath = domainAuthResourcesWildMatch.item(i);
            if (WildMatch(resource, wildResourcePath, true))
                return true;
        }
        return false;
    }
    void readAuthDomainCfg(IPropertyTree* procCfg);
    void readUnrestrictedResources(const char* resources);
    void setSDSSession();

    static void escapeSingleQuote(StringBuffer& src, StringBuffer& escaped);

protected:
    virtual bool basicAuth(IEspContext* ctx);
    int getWsdlOrXsd(IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *service, const char *method, bool isWsdl);
    virtual bool getSchema(StringBuffer& schema, IEspContext &ctx, CHttpRequest* req, const char *service, const char *method,bool standalone);
    virtual void appendSchemaNamespaces(IPropertyTree *namespaces, IEspContext &ctx, CHttpRequest* req, const char *service, const char *method){}
    void generateSampleXml(bool isRequest, IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method);
    void generateSampleXml(bool isRequest, IEspContext &context, CHttpRequest* request, StringBuffer &content, const char *serv, const char *method);
    void generateSampleJson(bool isRequest, IEspContext &context, CHttpRequest* request, StringBuffer &content, const char *serv, const char *method);
    void generateSampleJson(bool isRequest, IEspContext &context, CHttpRequest* request, CHttpResponse* response,    const char *serv, const char *method);
    void generateSampleXmlFromSchema(bool isRequest, IEspContext &context, CHttpRequest* request, CHttpResponse* response, const char *serv, const char *method, const char * schemaxml);
    virtual void getSoapMessage(StringBuffer& soapmsg, IEspContext &context, CHttpRequest* request, const char *serv, const char *method);
    void onBeforeSendResponse(IEspContext& context, CHttpRequest* request,MemoryBuffer& contentconst,
                            const char *serviceName, const char* methodName);
    void validateResponse(IEspContext& context, CHttpRequest* request,MemoryBuffer& contentconst,
                            const char *serviceName, const char* methodName);
    void sortResponse(IEspContext& context, CHttpRequest* request,MemoryBuffer& contentconst,
                            const char *serviceName, const char* methodName);
};

inline bool isEclIdeRequest(CHttpRequest *request)
{
    StringBuffer userAgent;
    return strstr(request->getHeader("User-Agent", userAgent), "eclide/") != NULL;
}

inline bool checkInitEclIdeResponse(CHttpRequest *request, CHttpResponse* response)
{
    if (isEclIdeRequest(request))
    {
        response->addHeader("X-UA-Compatible", "IE=edge");
        return true;
    }
    return false;
}

#endif //_SOAPBIND_HPP__

#include "TRootSnifferStore.h"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TRootSnifferStore                                                    //
//                                                                      //
// Used to store different results of objects scanning by TRootSniffer  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// normal constructor

TRootSnifferStore::TRootSnifferStore() :
   TObject(),
   fResPtr(0),
   fResClass(0),
   fResMember(0),
   fResNumChilds(-1)
{
}

////////////////////////////////////////////////////////////////////////////////
/// destructor

TRootSnifferStore::~TRootSnifferStore()
{
}

////////////////////////////////////////////////////////////////////////////////
/// set pointer on found element, class and number of childs

void TRootSnifferStore::SetResult(void *_res, TClass *_rescl,
                                  TDataMember *_resmemb, Int_t _res_chld)
{
   fResPtr = _res;
   fResClass = _rescl;
   fResMember = _resmemb;
   fResNumChilds = _res_chld;
}

// =================================================================================

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TRootSnifferStoreXml                                                 //
//                                                                      //
// Used to store scanned objects hierarchy in XML form                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// starts new xml node, will be closed by CloseNode

void TRootSnifferStoreXml::CreateNode(Int_t lvl, const char *nodename)
{
   buf->Append(TString::Format("%*s<%s", compact ? 0 : (lvl+1) * 2, "", nodename));
}

////////////////////////////////////////////////////////////////////////////////
/// set field (xml attribute) in current node

void TRootSnifferStoreXml::SetField(Int_t, const char *field, const char *value,
                                    Bool_t)
{
   if (strpbrk(value, "<>&\'\"") == 0) {
      buf->Append(TString::Format(" %s=\"%s\"", field, value));
   } else {
      buf->Append(TString::Format(" %s=\"", field));
      const char *v = value;
      while (*v != 0) {
         switch (*v) {
            case '<' :
               buf->Append("&lt;");
               break;
            case '>' :
               buf->Append("&gt;");
               break;
            case '&' :
               buf->Append("&amp;");
               break;
            case '\'' :
               buf->Append("&apos;");
               break;
            case '\"' :
               buf->Append("&quot;");
               break;
            default:
               buf->Append(*v);
               break;
         }
         v++;
      }

      buf->Append("\"");
   }
}

////////////////////////////////////////////////////////////////////////////////
/// called before next child node created

void TRootSnifferStoreXml::BeforeNextChild(Int_t, Int_t nchld, Int_t)
{
   if (nchld == 0) buf->Append(TString::Format(">%s", (compact ? "" : "\n")));
}

////////////////////////////////////////////////////////////////////////////////
/// called when node should be closed
/// depending from number of childs different xml format is applied

void TRootSnifferStoreXml::CloseNode(Int_t lvl, const char *nodename,
                                     Int_t numchilds)
{
   if (numchilds > 0)
      buf->Append(TString::Format("%*s</%s>%s", compact ? 0 : (lvl+1) * 2, "", nodename, (compact ? "" : "\n")));
   else
      buf->Append(TString::Format("/>%s", (compact ? "" : "\n")));
}

// ============================================================================

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TRootSnifferStoreXml                                                 //
//                                                                      //
// Used to store scanned objects hierarchy in JSON form                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// starts new json object, will be closed by CloseNode

void TRootSnifferStoreJson::CreateNode(Int_t lvl, const char *nodename)
{
   buf->Append(TString::Format("%*s{", compact ? 0 : lvl * 4, ""));
   if (!compact) buf->Append("\n");
   buf->Append(TString::Format("%*s\"_name\"%s\"%s\"", compact ? 0 : lvl * 4 + 2, "", (compact ? ":" : " : "), nodename));
}

////////////////////////////////////////////////////////////////////////////////
/// set field (json field) in current node

void TRootSnifferStoreJson::SetField(Int_t lvl, const char *field,
                                     const char *value, Bool_t with_quotes)
{
   buf->Append(",");
   if (!compact) buf->Append("\n");
   buf->Append(TString::Format("%*s\"%s\"%s", compact ? 0 : lvl * 4 + 2, "", field, (compact ? ":" : " : ")));
   if (with_quotes) {
      buf->Append(TString::Format("\"%s\"", value));
   } else {
      buf->Append(value);
   }
}

////////////////////////////////////////////////////////////////////////////////
/// called before next child node created

void TRootSnifferStoreJson::BeforeNextChild(Int_t lvl, Int_t nchld, Int_t)
{
   buf->Append(",");
   if (!compact) buf->Append("\n");
   if (nchld == 0)
      buf->Append(TString::Format("%*s\"_childs\"%s", (compact ? 0 : lvl * 4 + 2), "", (compact ? ":[" : " : [\n")));
}

////////////////////////////////////////////////////////////////////////////////
/// called when node should be closed
/// depending from number of childs different xml format is applied

void TRootSnifferStoreJson::CloseNode(Int_t lvl, const char *, Int_t numchilds)
{
   if (numchilds > 0)
      buf->Append(TString::Format("%s%*s]", (compact ? "" : "\n"), compact ? 0 : lvl * 4 + 2, ""));
   buf->Append(TString::Format("%s%*s}", (compact ? "" : "\n"), compact ? 0 : lvl * 4, ""));
}


# include <iostream>
# include <vector>
# include <stdio.h>
# include <stdlib.h>
# include <stdexcept>
# include <iomanip>
# include <string>
# include <string.h>
# include <sstream>
using namespace std ;


struct CharToken {
  char lexical[100] ;
  int type ;
    // LP     : 1   RP     : 2
    // Dot    : 3   NIL    : 4
    // T      : 5   Quote  : 6
    // Int    : 7   Float  : 8
    // String : 9   Symbol : 10
    // 指令 : 11 
};

struct TreeType {
  vector<CharToken> data ;
  TreeType * leftC ;
  TreeType * rightC ;
};

struct DefineSymbolListType{
  string symbolName ;
  TreeType *treeData ; 
};

typedef TreeType * TreeTypePointer ;

class Project2 {
  private:
  // ---------------------------------------------------P2
  TreeType *m_treeRoot ;
  TreeType *m_ErrorMsgIfCond ;
  TreeType *m_ErrorMsgTreeRoot ;
  vector<string> m_presetSymbolList ;
  vector<DefineSymbolListType> m_defineSymbolList ;
  // symbol type : cons, list, quote, define, car, cdr
  
  void CreateDefineSymbolList() {
    PushPresetSymbolInToSymbolList( "quote" )  ;
    PushPresetSymbolInToSymbolList( "cons" )  ;
    PushPresetSymbolInToSymbolList( "list" ) ;
    PushPresetSymbolInToSymbolList( "define" ) ;
    PushPresetSymbolInToSymbolList( "car" ) ;
    PushPresetSymbolInToSymbolList( "cdr" ) ;
    PushPresetSymbolInToSymbolList( "atom?" ) ;
    PushPresetSymbolInToSymbolList( "pair?" ) ;
    PushPresetSymbolInToSymbolList( "list?" ) ;
    PushPresetSymbolInToSymbolList( "null?" ) ;
    PushPresetSymbolInToSymbolList( "integer?" ) ;
    PushPresetSymbolInToSymbolList( "real?" ) ;
    PushPresetSymbolInToSymbolList( "number?" ) ;
    PushPresetSymbolInToSymbolList( "string?" ) ;
    PushPresetSymbolInToSymbolList( "boolean?" ) ;
    PushPresetSymbolInToSymbolList( "symbol?" ) ;
    PushPresetSymbolInToSymbolList( "+" ) ;
    PushPresetSymbolInToSymbolList( "-" ) ;
    PushPresetSymbolInToSymbolList( "*" ) ;
    PushPresetSymbolInToSymbolList( "/" ) ;
    PushPresetSymbolInToSymbolList( "not" ) ;
    PushPresetSymbolInToSymbolList( "and" ) ;
    PushPresetSymbolInToSymbolList( "or" ) ;
    PushPresetSymbolInToSymbolList( ">" ) ;
    PushPresetSymbolInToSymbolList( ">=" ) ;
    PushPresetSymbolInToSymbolList( "<" ) ;
    PushPresetSymbolInToSymbolList( "<=" ) ;
    PushPresetSymbolInToSymbolList( "=" ) ;
    PushPresetSymbolInToSymbolList( "string-append" ) ;
    PushPresetSymbolInToSymbolList( "string>?" ) ;
    PushPresetSymbolInToSymbolList( "string<?" ) ;
    PushPresetSymbolInToSymbolList( "string=?" ) ;
    PushPresetSymbolInToSymbolList( "eqv?" ) ;
    PushPresetSymbolInToSymbolList( "equal?" ) ;
    PushPresetSymbolInToSymbolList( "begin" ) ;
    PushPresetSymbolInToSymbolList( "if" ) ;
    PushPresetSymbolInToSymbolList( "cond" ) ;
    PushPresetSymbolInToSymbolList( "clean-environment" ) ;
    PushPresetSymbolInToSymbolList( "exit" ) ;
  } // CreateDefineSymbolList()
  
  void CreatePresetSymbolList() {
    m_presetSymbolList.push_back( "quote" ) ;
    m_presetSymbolList.push_back( "cons" ) ;
    m_presetSymbolList.push_back( "list" ) ;
    m_presetSymbolList.push_back( "define" ) ;
    m_presetSymbolList.push_back( "car" ) ;
    m_presetSymbolList.push_back( "cdr" ) ;
    m_presetSymbolList.push_back( "atom?" ) ;
    m_presetSymbolList.push_back( "pair?" ) ;
    m_presetSymbolList.push_back( "list?" ) ;
    m_presetSymbolList.push_back( "null?" ) ;
    m_presetSymbolList.push_back( "integer?" ) ;
    m_presetSymbolList.push_back( "real?" ) ;
    m_presetSymbolList.push_back( "number?" ) ;
    m_presetSymbolList.push_back( "string?" ) ;
    m_presetSymbolList.push_back( "boolean?" ) ;
    m_presetSymbolList.push_back( "symbol?" ) ;
    m_presetSymbolList.push_back( "+" ) ;
    m_presetSymbolList.push_back( "-" ) ;
    m_presetSymbolList.push_back( "*" ) ;
    m_presetSymbolList.push_back( "/" ) ;
    m_presetSymbolList.push_back( "not" ) ;
    m_presetSymbolList.push_back( "and" ) ;
    m_presetSymbolList.push_back( "or" ) ;
    m_presetSymbolList.push_back( ">" ) ;
    m_presetSymbolList.push_back( ">=" ) ;
    m_presetSymbolList.push_back( "<" ) ;
    m_presetSymbolList.push_back( "<=" ) ;
    m_presetSymbolList.push_back( "=" ) ;
    m_presetSymbolList.push_back( "string-append" ) ;
    m_presetSymbolList.push_back( "string>?" ) ;
    m_presetSymbolList.push_back( "string<?" ) ;
    m_presetSymbolList.push_back( "string=?" ) ;
    m_presetSymbolList.push_back( "eqv?" ) ;
    m_presetSymbolList.push_back( "equal?" ) ;
    m_presetSymbolList.push_back( "begin" ) ;
    m_presetSymbolList.push_back( "if" ) ;
    m_presetSymbolList.push_back( "cond" ) ;
    m_presetSymbolList.push_back( "clean-environment" ) ;
    m_presetSymbolList.push_back( "exit" ) ;
  } // CreatePresetSymbolList()

  void PushPresetSymbolInToSymbolList( string sName ) { // 輸入名字建立指令 
    TreeType *newSymbol = new TreeType ;
    CharToken symbolData ;
    strcpy( symbolData.lexical, "" ) ;
    strcat( symbolData.lexical, "#<procedure " ) ; 
    strcat( symbolData.lexical, sName.c_str() ) ; 
    strcat( symbolData.lexical, ">" ) ; 
    symbolData.type = 11 ;
      
    newSymbol->data.push_back( symbolData ) ; // 建立一個新節點 
    newSymbol->leftC = NULL ;
    newSymbol->rightC = NULL ;
    
    DefineSymbolListType newType ; // 放入LIST中 
    newType.symbolName = sName ;
    newType.treeData = newSymbol ;
    m_defineSymbolList.push_back( newType ) ;
    return ;
  } // PushPresetSymbolInToSymbolList()
  
  bool IsInPresetSymbolList( string inSymbol ) {
    for ( int i = 0 ; i < m_presetSymbolList.size() ; i++ ) {
      if ( inSymbol == m_presetSymbolList[i] )
        return true ;
    } // for
    
    return false ;
  } // IsInPresetSymbolList()
  
  string ChangeCharToStr( char inChar[100] ) {
    string out ;
    for ( int i = 0 ; i < strlen( inChar ) ; i++ ) {
      out = out + inChar[i] ;
    } // for

    return out ;
  } // ChangeCharToStr()
  
  bool IsInDefineSymbolList( string inSymbol ) {

    for ( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
      if ( inSymbol == m_defineSymbolList[i].symbolName )
        return true ;
    } // for
    
    return false ;
  } // IsInDefineSymbolList()
  
  bool TheEndIsNIL( TreeType *nowSpace ) { // 判斷最右下子樹是不是NIL 
    TreeType *tempNowSpace = nowSpace ;
    while ( tempNowSpace -> data.size() == 0 ) {
      tempNowSpace = tempNowSpace -> rightC ;
    } // while

    if ( tempNowSpace->data[0].type == 4 ) { // is nil
      return true ;
    } // if
    
    return false ;
    
  } // TheEndIsNIL()
  
  int CountChiledTree( TreeType *nowSpace ) { // 計算有幾棵子樹 
    TreeType *tempNowSpace = nowSpace ;
    int count = 0 ;
    while ( tempNowSpace -> data.size() == 0 ) {
      count++ ;
      tempNowSpace = tempNowSpace -> rightC ;
    } // while

    return count ;
  } // CountChiledTree()

  // num1
  bool DoQuote( TreeType *nowSpace, TreeTypePointer &outSpace ) { // 要傳原本的右子樹當nowSpace 

    outSpace = nowSpace ;
    return true ;
  } // DoQuote()
  
  bool DoCons( TreeType *nowSpace, TreeTypePointer &outSpace ) { // 要傳原本的右子樹當nowSpace 

    // 1. 先判斷是不是nil結尾，不是就出NON-LIST ERROR，印出原指令 
    // 2. 判斷後面有幾棵子樹，如果不是兩棵就出incorrect number of arguments，印出cons
    // 3. 判斷所有子樹是不是可以接的( quote 或 其他非指令 ??)有錯出 NON-LIST ERROR
    //    同時判斷有沒有attempt to apply non-function
    TreeType *tempSpace = nowSpace ;
    if ( TheEndIsNIL( tempSpace ) ) { // 1
      if ( CountChiledTree( tempSpace ) == 2 ) { // 2 (有兩棵子樹)
        // 開始判斷是不是都是可以接的
        TreeType *firstTree ; // 要放在左邊的 
        TreeType *secondTree ; // 要放在右邊的 
        EvalSymbol( tempSpace->leftC, firstTree, false ) ;
        EvalSymbol( tempSpace->rightC->leftC, secondTree, false ) ;
        outSpace = new TreeType ;
        outSpace->data.clear() ;
        outSpace->leftC = firstTree ;
        outSpace->rightC = secondTree ;
        return true ;
      } // if
      else {
        throw ( "ERROR (incorrect number of arguments) : cons"  ) ;
        return false ;
      } // else
    } // if
    else { // 1
      throw ( "ERROR (non-list) : " ) ; 
      return false ;
    } // else
    
  } // DoCons()
  // num1
  // num2
  
  bool DoList( TreeType *nowSpace, TreeTypePointer &outSpace ) { // 要傳原本的右子樹當nowSpace  
    TreeType *tempSpace = nowSpace ;
    outSpace = new TreeType ;
    outSpace->data.clear() ;
    outSpace->leftC = NULL ;
    outSpace->rightC = NULL ;
    TreeType *tempOut = outSpace ;
    if ( TheEndIsNIL( tempSpace ) ) { // Is List
      if ( CountChiledTree( tempSpace ) > 0  ) { // 大於等於一棵  
        while ( tempSpace->data.size() == 0 || 
                ( tempSpace->data.size() > 0 && tempSpace->data[0].type != 4 ) ) { // 走到NIL為止
          TreeType *nextTree = NULL ;
          EvalSymbol( tempSpace->leftC, nextTree, false ) ;
          tempOut->leftC = nextTree ;
          tempOut->rightC = new TreeType ;
          tempOut = tempOut->rightC ;
          tempSpace = tempSpace -> rightC ;
        } // while 
      
        CharToken nilToken ;
        strcpy( nilToken.lexical, "nil" ) ;
        nilToken.type = 4 ;
        tempOut->data.push_back( nilToken ) ;
        tempOut->leftC = NULL ;
        tempOut->rightC = NULL ;
        return true ;
      } // if
      else {
        CharToken nilToken ;
        strcpy( nilToken.lexical, "nil" ) ;
        nilToken.type = 4 ;
        tempOut->data.push_back( nilToken ) ;
        tempOut->leftC = NULL ;
        tempOut->rightC = NULL ;
        return true ;
        // throw ( "ERROR (incorrect number of arguments) : list"  ) ;
        // return false ;
      } // else
    } // if
    else { // 1
      throw ( "ERROR (non-list) : " ) ; 
      return false ;
    } // else
    
  } // DoList()
  
  // num2
  // num3
  bool IsRedefindPrimitive( TreeType *nowSpace ) { // 判斷是不是初始指令要被define 
    if ( nowSpace->leftC->data.size() == 0 ) { // 如果左邊是樹? 06/03回傳錯誤 
      throw ( "ERROR (DEFINE format) : " ) ;
      return false ;
    } // if

    for ( int i = 0 ; i < m_presetSymbolList.size() ; i++ ) {
      if ( m_presetSymbolList[i] == ChangeCharToStr( nowSpace->leftC->data[0].lexical ) )
        return true ;    
    } // for
    
    return false ;
      
  } // IsRedefindPrimitive()
  
  bool CheckDefineFormat( TreeType *nowSpace ) { // 要傳原本的右子樹當nowSpace
    if ( CountChiledTree( nowSpace ) != 2 ) {
      throw ( "ERROR (DEFINE format) : " ) ;
      return false ;
    } // if
    else {
      if ( IsRedefindPrimitive( nowSpace ) ) {
        throw ( "ERROR (DEFINE format) : " ) ;
        return false ;
      } // if
      else {
        if ( nowSpace->leftC->data.size() > 0 ) { // 判斷左邊是一個東西 
          if ( nowSpace->leftC->data[0].type == 10 ) { // 左邊那個是symbol 
            DefineSymbolListType newSymbol ;
            newSymbol.symbolName = ChangeCharToStr( nowSpace->leftC->data[0].lexical ) ;

            EvalSymbol( nowSpace->rightC->leftC, newSymbol.treeData, false ) ;

            for ( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
              if ( m_defineSymbolList[i].symbolName == newSymbol.symbolName ) {
                m_defineSymbolList[i].treeData = newSymbol.treeData ;
                cout << nowSpace->leftC->data[0].lexical << " defined\n" ; 
                return true ;
              } // if
            } // for

            m_defineSymbolList.push_back( newSymbol ) ;
            cout << nowSpace->leftC->data[0].lexical << " defined\n" ; 
            return true ;
          } // if
          else {
            throw ( "ERROR (DEFINE format) : " ) ;
            return false ;
          } // else
        } // if 
        else {
          throw ( "ERROR (DEFINE format) : " ) ;
          return false ;
        } // else
      } // else
    } // else
    
    return true ;
  } // CheckDefineFormat()
  
  bool DoDefine( TreeType *nowSpace ) { // 要傳原本的右子樹當nowSpace  
    /*
    for( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
        cout << " m_defineSymbolList[i]: " << m_defineSymbolList[i].symbolName << endl ;
    } // for
    */
    if ( CheckDefineFormat( nowSpace ) ) {
        
    /*
        cout << "\n-----AFTER DEFIND-----\n" ;
          for( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
            cout << " m_defineSymbolList[i]: " << m_defineSymbolList[i].symbolName << endl ;
        } // for
    */
      return true ;
    } // if
    
    
    
    return false ;
  } // DoDefine() 
  
  // num3
  // num4
  bool DoCar( TreeType *nowSpace, TreeTypePointer &outSpace ) {
      // cout << "do Car!\n" ;
    TreeType *tempSpace = nowSpace ;
    if ( TheEndIsNIL( tempSpace ) ) { // 1
      if ( CountChiledTree( tempSpace ) == 1 ) { 
        // 開始判斷是不是都是可以接的
        TreeType *firstTree ; // 要放在左邊的 
        EvalSymbol( tempSpace->leftC, firstTree, false ) ;
        if ( firstTree->data.size() > 0 ) {
          // string errorMsg = CharToString( firstTree ) ;
          m_ErrorMsgTreeRoot = firstTree ;
          throw ( "ERROR (car with incorrect argument type) : " ) ;
          return false ;
        } // if
        
        outSpace = firstTree->leftC ;
        // cout << "end Car!\n" ;
        return true ;
      } // if
      else {
        throw ( "ERROR (incorrect number of arguments) : car"  ) ;
        return false ;
      } // else
    } // if
    else { // 1
      throw ( "ERROR (non-list) : " ) ; 
      return false ;
    } // else
  } // DoCar()
  
  bool DoCdr( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *tempSpace = nowSpace ;
    if ( TheEndIsNIL( tempSpace ) ) { // 1
      if ( CountChiledTree( tempSpace ) == 1 ) { // 2 (有兩棵子樹)
        // 開始判斷是不是都是可以接的
        TreeType *firstTree ; // 要放在左邊的 
        EvalSymbol( tempSpace->leftC, firstTree, false ) ;
        if ( firstTree->data.size() > 0 ) {
          // string errorMsg = CharToString( firstTree ) ;
          m_ErrorMsgTreeRoot = firstTree ;
          throw ( "ERROR (cdr with incorrect argument type) : " ) ;
          return false ;
        } // if

        outSpace = firstTree->rightC ;
        return true ;
      } // if
      else {
        throw ( "ERROR (incorrect number of arguments) : cdr"  ) ;
        return false ;
      } // else
    } // if
    else { // 1
      throw ( "ERROR (non-list) : " ) ; 
      return false ;
    } // else
  } // DoCdr()
  
  // num4
  // num5
  TreeType *CreateTFAtom( bool isTrue ) {
    TreeType *outTree = new TreeType ;
    CharToken tfToken ;
    if ( isTrue ) {
      strcpy( tfToken.lexical, "#t" ) ;
      tfToken.type = 5 ;
    } // if
    else {
      strcpy( tfToken.lexical, "nil" ) ;
      tfToken.type = 4 ;
    } // else

    outTree -> data.push_back( tfToken ) ;
    outTree -> rightC = NULL ;
    outTree -> leftC = NULL ;
    return outTree ;
  } // CreateTFAtom()
  
  bool TreeIsAtom( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : atom?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() != 0 ) {
      outSpace = CreateTFAtom( true ) ;
      // cout << "true\n" ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else
    
    return false ;
  } // TreeIsAtom()
  
  bool TreeIsPair( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : pair?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() != 0 ) {
      outSpace = CreateTFAtom( false ) ;
      // cout << "false\n" ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // else
    
    return false ;
  } // TreeIsPair()
  
  bool TreeIsList( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : list?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( TheEndIsNIL( symbolOut ) ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else
  } // TreeIsList()
  
  bool TreeIsNull( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : null?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 4 ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else
    
  } // TreeIsNull()
  
  bool TreeIsInteger( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : integer?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 7 ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else
  } // TreeIsInteger()
  
  bool TreeIsReal( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : real?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && 
         ( symbolOut->data[0].type == 7 || symbolOut->data[0].type == 8 ) ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // TreeIsReal()
  
  bool TreeIsNumber( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : number?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && 
         ( symbolOut->data[0].type == 7 || symbolOut->data[0].type == 8 ) ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // TreeIsNumber()
  
  bool TreeIsString( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : string?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 9 ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // TreeIsString()
  
  bool TreeIsBoolean( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : boolean?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && 
         ( symbolOut->data[0].type == 4 || nowSpace->leftC->data[0].type == 5 ) ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // TreeIsBoolean()
  
  bool TreeIsSymbol( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : symbol?" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 10 ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // TreeIsSymbol()
  // num5
  // num6
  bool AllChildAreNum( TreeType *nowSpace, TreeTypePointer &errorSpace ) {
      
    while ( nowSpace->data.size() == 0 ) {
      TreeType *symbolOut = NULL ;
      EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
      if ( symbolOut->data.size() > 0 && 
           ( symbolOut->data[0].type == 7 || symbolOut->data[0].type == 8 ) ) ;
      else {
        errorSpace = symbolOut ;
        return false ;
      } // else
      
      nowSpace = nowSpace->rightC ;
    } // while
    
    return true ;
  } // AllChildAreNum()
  
  bool HaveFloatChild( TreeType *nowSpace ) {
    while ( nowSpace->data.size() == 0 ) {
      TreeType *symbolOut = NULL ;
      EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
      if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 8 ) 
        return true ;
      nowSpace = nowSpace->rightC ;
    } // while
    
    return false ;
  } // HaveFloatChild()

  int GetIntChildNum( TreeType *nowSpace ) {
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
    return atoi( symbolOut->data[0].lexical ) ;
  } // GetIntChildNum()
  
  float GetFloatChildNum( TreeType *nowSpace ) {
    TreeType *symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
    return atof( symbolOut->data[0].lexical ) ;
  } // GetFloatChildNum()

  TreeType *CreateNumAtom( bool haveFolat, char inChar[100] ) {
    TreeType *outTree = new TreeType ;
    CharToken tfToken ;
    if ( haveFolat ) {
      strcpy( tfToken.lexical, inChar ) ;
      tfToken.type = 8 ;
    } // if
    else {
      strcpy( tfToken.lexical, inChar ) ;
      tfToken.type = 7 ;
    } // else

    outTree -> data.push_back( tfToken ) ;
    outTree -> rightC = NULL ;
    outTree -> leftC = NULL ;
    return outTree ;
  } // CreateNumAtom()

  string ChangeIntToString( int num ) {
    stringstream ss ;
    string intStr ;
    ss << num ;
    ss >> intStr ;
    return intStr ;
  } // ChangeIntToString()

  string ChangeFloatToString( float num ) {
    stringstream ss ;
    string floatStr ;
    ss << num ;
    ss >> floatStr ;
    return floatStr ;
  } // ChangeFloatToString()

  string CharToString( TreeType *notAllNumError ) {
    
    string errorMsg = "" ;
    for ( int i = 0 ; i < notAllNumError->data.size() ; i++ ) {
      string tempMsg = "" ;
      char *tempChar = new char ;
      strcpy( tempChar, notAllNumError->data[i].lexical ) ;
      tempMsg.assign( tempChar ) ;
      errorMsg = errorMsg + tempMsg ;
    } // for
    // cout << "test!!!!\n" ;
    return errorMsg ;
  } // CharToString()

  bool IsAdd( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;

    if ( CountChiledTree( nowSpace ) < 2 ) { 
        
      throw ( "ERROR (incorrect number of arguments) : +" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (+ with incorrect argument type) : " ) ;
      return false ;
    } // if

    bool haveFloat = HaveFloatChild( nowSpace ) ;
    if ( !haveFloat ) {
      int outNum = 0 ;
      while ( nowSpace->data.size() == 0 ) {

        outNum = outNum + GetIntChildNum( nowSpace ) ;

        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      
      // itoa( outNum, numChar, 10 ) ;
      strcpy( numChar, ChangeIntToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // if
    else {
      float outNum = 0 ;
      while ( nowSpace->data.size() == 0 ) {
        outNum = outNum + GetFloatChildNum( nowSpace ) ;
        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      strcpy( numChar, ChangeFloatToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // else
    

    return true ;
  } // IsAdd()
  
  bool IsSub( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;

    if ( CountChiledTree( nowSpace ) < 2 ) { 
        
      throw ( "ERROR (incorrect number of arguments) : -" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (- with incorrect argument type) : " ) ;
      return false ;
    } // if

    bool haveFloat = HaveFloatChild( nowSpace ) ;
    if ( !haveFloat ) {
      int outNum = GetIntChildNum( nowSpace ) ;
      nowSpace = nowSpace->rightC ;
      while ( nowSpace->data.size() == 0 ) {
        outNum = outNum - GetIntChildNum( nowSpace ) ;
        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      strcpy( numChar, ChangeIntToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // if
    else {
      float outNum = GetFloatChildNum( nowSpace ) ;
      nowSpace = nowSpace->rightC ;
      while ( nowSpace->data.size() == 0 ) {
        outNum = outNum - GetFloatChildNum( nowSpace ) ;
        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      
      strcpy( numChar, ChangeFloatToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // else
    

    return true ;
  } // IsSub()
  
  bool IsMul( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;

    if ( CountChiledTree( nowSpace ) < 2 ) { 
        
      throw ( "ERROR (incorrect number of arguments) : *" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (* with incorrect argument type) : " ) ;
      return false ;
    } // if

    bool haveFloat = HaveFloatChild( nowSpace ) ;
    if ( !haveFloat ) {
      int outNum = 1 ;
      while ( nowSpace->data.size() == 0 ) {

        outNum = outNum * GetIntChildNum( nowSpace ) ;

        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      strcpy( numChar, ChangeIntToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // if
    else {
      float outNum = 1 ;
      while ( nowSpace->data.size() == 0 ) {
        outNum = outNum * GetFloatChildNum( nowSpace ) ;
        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      
      strcpy( numChar, ChangeFloatToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // else
    

    return true ;
  } // IsMul()
  
  bool IsDiv( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;

    if ( CountChiledTree( nowSpace ) < 2 ) { 
        
      throw ( "ERROR (incorrect number of arguments) : /" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (/ with incorrect argument type) : " ) ;
      return false ;
    } // if

    bool haveFloat = HaveFloatChild( nowSpace ) ;
    if ( !haveFloat ) {
      int outNum = GetIntChildNum( nowSpace ) ;
      nowSpace = nowSpace->rightC ;
      while ( nowSpace->data.size() == 0 ) {
        if ( GetIntChildNum( nowSpace ) == 0 ) {
          throw ( "ERROR (division by zero) : /" ) ;
        } // if
          
        outNum = outNum / GetIntChildNum( nowSpace ) ;
        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      strcpy( numChar, ChangeIntToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // if
    else {
      float outNum = GetFloatChildNum( nowSpace ) ;
      nowSpace = nowSpace->rightC ;
      while ( nowSpace->data.size() == 0 ) {
        if ( GetIntChildNum( nowSpace ) == 0 ) {
          throw ( "ERROR (division by zero) : /" ) ;
        } // if
        
        outNum = outNum / GetFloatChildNum( nowSpace ) ;
        nowSpace = nowSpace->rightC ;
      } // while
      
      char numChar[100] ;
      
      strcpy( numChar, ChangeFloatToString( outNum ).c_str() ) ;
      outSpace = CreateNumAtom( haveFloat, numChar ) ;
    } // else
    

    return true ;
  } // IsDiv()
  
  bool IsNot( TreeType *nowSpace, TreeTypePointer &outSpace ) { // 不確定功能 先設為判斷false 
    if ( CountChiledTree( nowSpace ) != 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : not" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;

    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;

    if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 4 ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // IsNot()
  
  bool IsAnd( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : and" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      symbolOut = NULL ;
      EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
      if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 4 ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
    outSpace = symbolOut ;
    return true ;
  } // IsAnd()
  
  bool IsOr( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : or" ) ;
      return false ;
    } // if
    
    TreeType *symbolOut = NULL ;
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      symbolOut = NULL ;
      EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
      
      if ( symbolOut->data.size() > 0 && symbolOut->data[0].type != 4 ) {
        outSpace = symbolOut ;
        return true ;
      } // if
      else if ( symbolOut->data.size() == 0 ) {
        outSpace = symbolOut ;
        return true ;
      } // else if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    symbolOut = NULL ;
    EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
    outSpace = symbolOut ;
    return true ;
  } // IsOr()
  
  bool IsBigThan( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : >" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (> with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      if ( GetFloatChildNum( nowSpace ) <= GetFloatChildNum( nextTree ) ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;

  } // IsBigThan()
  
  bool IsBigEqualThan( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : >=" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (>= with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      if ( GetFloatChildNum( nowSpace ) < GetFloatChildNum( nextTree ) ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;

  } // IsBigEqualThan()
  
  bool IsSmallThan( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : <" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (< with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      if ( GetFloatChildNum( nowSpace ) >= GetFloatChildNum( nextTree ) ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;

  } // IsSmallThan()

  bool IsSmallEqualThan( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : <=" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (<= with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      if ( GetFloatChildNum( nowSpace ) > GetFloatChildNum( nextTree ) ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;

  } // IsSmallEqualThan()
  
  bool IsEqualThan( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : =" ) ;
      return false ;
    } // if

    if ( !AllChildAreNum( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (= with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      if ( GetFloatChildNum( nowSpace ) != GetFloatChildNum( nextTree ) ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;

  } // IsEqualThan()
  
  bool AllChildAreString( TreeType *nowSpace, TreeTypePointer &errorSpace ) {
      
    while ( nowSpace->data.size() == 0 ) {
      TreeType *symbolOut = NULL ;
      EvalSymbol( nowSpace->leftC, symbolOut, false ) ;
      if ( symbolOut->data.size() > 0 && symbolOut->data[0].type == 9 ) ;
      else {
        errorSpace = symbolOut ;
        return false ;
      } // else
      
      nowSpace = nowSpace->rightC ;
    } // while
    
    return true ;
  } // AllChildAreString()

  bool IsStringAppend( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : string-append" ) ;
      return false ;
    } // if

    if ( !AllChildAreString( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (string-append with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    CharToken twoPointToken1 ;
    strcpy( twoPointToken1.lexical, "\"" ) ;
    twoPointToken1.type = 9 ;
    CharToken twoPointToken2 ;
    strcpy( twoPointToken2.lexical, "\"" ) ;
    twoPointToken2.type = 9 ;
    CharToken stringToken ;
    strcpy( stringToken.lexical, "" ) ;
    stringToken.type = 9 ;
    
    for ( int i = 0 ; i < childTreeNum ; i++ ) {
      TreeType *stringSpace = NULL ;
      EvalSymbol( nowSpace->leftC, stringSpace, false ) ;
      strcat( stringToken.lexical, stringSpace->data[1].lexical ) ;
      nowSpace = nowSpace->rightC ;
    } // for
    
    
    outSpace = new TreeType ;
    outSpace->data.push_back( twoPointToken1 ) ;
    outSpace->data.push_back( stringToken ) ;
    outSpace->data.push_back( twoPointToken2 ) ;
    outSpace->rightC = NULL ;
    outSpace->leftC = NULL ;
    return true ;
  } // IsStringAppend()
  
  bool IsStringBig( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : string>?" ) ;
      return false ;
    } // if

    if ( !AllChildAreString( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (string>? with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      TreeType *outNowStr = NULL ;
      TreeType *outNextStr = NULL ;
      EvalSymbol( nowSpace->leftC, outNowStr, false ) ;
      EvalSymbol( nextTree->leftC, outNextStr, false ) ;
      if ( strcmp( outNowStr->data[1].lexical, outNextStr->data[1].lexical ) <= 0 ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;
      
  } // IsStringBig()
  
  bool IsStringSmall( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : string<?" ) ;
      return false ;
    } // if

    if ( !AllChildAreString( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (string<? with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      TreeType *outNowStr = NULL ;
      TreeType *outNextStr = NULL ;
      EvalSymbol( nowSpace->leftC, outNowStr, false ) ;
      EvalSymbol( nextTree->leftC, outNextStr, false ) ;
      if ( strcmp( outNowStr->data[1].lexical, outNextStr->data[1].lexical ) >= 0 ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;
  } // IsStringSmall()
  
  bool IsStringEqual( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : string=?" ) ;
      return false ;
    } // if

    if ( !AllChildAreString( nowSpace, notAllNumError ) ) {
      // string errorMsg = CharToString( notAllNumError ) ;
      m_ErrorMsgTreeRoot = notAllNumError ;
      throw ( "ERROR (string=? with incorrect argument type) : " ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      TreeType *nextTree = nowSpace->rightC ;
      TreeType *outNowStr = NULL ;
      TreeType *outNextStr = NULL ;
      EvalSymbol( nowSpace->leftC, outNowStr, false ) ;
      EvalSymbol( nextTree->leftC, outNextStr, false ) ;
      if ( strcmp( outNowStr->data[1].lexical, outNextStr->data[1].lexical ) != 0 ) {
        outSpace = CreateTFAtom( false ) ;
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    outSpace = CreateTFAtom( true ) ;
    return true ;
  } // IsStringEqual()
  
  bool IsEqv( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum != 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : eqv?" ) ;
      return false ;
    } // if

    TreeType *nextTree = nowSpace->rightC ;
    TreeType *outNowT = NULL ;
    TreeType *outNextT = NULL ;
    EvalSymbol( nowSpace->leftC, outNowT, false ) ;
    EvalSymbol( nextTree->leftC, outNextT, false ) ;
    if ( outNowT == outNextT ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else if ( outNowT->data.size() > 0 && outNextT->data.size() > 0 &&
              outNowT->data.size() == outNextT->data.size() ) {
      for ( int i = 0 ; i < outNowT->data.size() ; i++ ) {
        if ( strcmp( outNowT->data[i].lexical, outNextT->data[i].lexical ) != 0 ||
             outNowT->data[i].type == 9 ) {
          outSpace = CreateTFAtom( false ) ;
          return true ;
        } // if
      } // for
      
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // else if

    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else

    return true ;
  } // IsEqv()
  
  bool TheTreeAreSame( TreeType *firstTree, TreeType *secondTree ) {
    if ( firstTree == NULL ) {
      if ( secondTree == NULL ) {
        return true ;
      } // if
      else {
        return false ;
      } // else
    } // if
    else if ( secondTree == NULL ) {
      if ( firstTree == NULL ) {
        return true ;
      } // if
      else {
        return false ;
      } // else
    } // else if
    else if ( TheTreeAreSame( firstTree->leftC, secondTree->leftC ) &&
              TheTreeAreSame( firstTree->rightC, secondTree->rightC ) ) {
      if ( firstTree->data.size() != secondTree->data.size() )
        return false ;
      else {
        for ( int i = 0 ; i < firstTree->data.size() ; i++ ) {
          if ( strcmp( firstTree->data[i].lexical, secondTree->data[i].lexical ) != 0 )
            return false ;
        } // for
        
        return true ;
      } // else
      
    } // else if
    
    return false ;
    
      
  } // TheTreeAreSame()
  
  bool IsEqual( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum != 2 ) { 
      throw ( "ERROR (incorrect number of arguments) : equal?" ) ;
      return false ;
    } // if

    TreeType *nextTree = nowSpace->rightC ;
    TreeType *outNowT = NULL ;
    TreeType *outNextT = NULL ;
    EvalSymbol( nowSpace->leftC, outNowT, false ) ;
    EvalSymbol( nextTree->leftC, outNextT, false ) ;
    if ( TheTreeAreSame( outNowT, outNextT ) ) {
      outSpace = CreateTFAtom( true ) ;
      return true ;
    } // if
    else {
      outSpace = CreateTFAtom( false ) ;
      return true ;
    } // else
      
    return false ;
  } // IsEqual()
  
  bool DoBegin( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    TreeType *notAllNumError = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 1 ) { 
      throw ( "ERROR (incorrect number of arguments) : begin" ) ;
      return false ;
    } // if
    
    
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      EvalSymbol( nowSpace->leftC, outSpace, false ) ;
      nowSpace = nowSpace->rightC ;
    } // for
    
    EvalSymbol( nowSpace->leftC, outSpace, false ) ;
    return true ;
  } // DoBegin()
  
  bool DoIf( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    outSpace = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum != 2 && childTreeNum != 3 ) { 
      throw ( "ERROR (incorrect number of arguments) : if" ) ;
      return false ;
    } // if
     
    TreeType *ifTrueAns = nowSpace->rightC ;
    TreeType *ifFalseAns = ifTrueAns->rightC ;
    TreeType *nowOut = NULL ;
    EvalSymbol( nowSpace->leftC, nowOut, false ) ;

    if ( nowOut->data.size() > 0 && nowOut->data[0].type == 4 ) {
      if ( ifFalseAns->data.size() == 0 )
        EvalSymbol( ifFalseAns->leftC, outSpace, false ) ;
    } // if 
    else {
      
      EvalSymbol( ifTrueAns->leftC, outSpace, false ) ;
      
    } // else
    
    if ( outSpace == NULL ) {
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (no return value) : " ) ;
      return false;
    } // if
    else
      return true ;
  } // DoIf()
  
  TreeType *SubTreeResult( TreeType *nowSpace ) { // 傳now->left 
    if ( !TheEndIsNIL( nowSpace ) ) {
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (COND format) : " ) ;
    } // if
    
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      // cout << childTreeNum ;
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (COND format) : " ) ;
    } // if
    
    TreeType *trueFlaseOut = NULL ;
    EvalSymbol( nowSpace->leftC, trueFlaseOut, false ) ;
    TreeType *returnTree = NULL ;
    if ( trueFlaseOut->data.size() > 0 && trueFlaseOut->data[0].type == 4 ) {
      return returnTree ;
    } // if
    else {
      for ( int i = 1 ; i < childTreeNum ; i++ ) {
        nowSpace = nowSpace->rightC ;
        EvalSymbol( nowSpace->leftC, returnTree, false ) ;
      } // for

    } // else
    
    return returnTree ;
  } // SubTreeResult()

  TreeType *GetElseResult( TreeType *nowSpace ) { // 同上
    if ( !TheEndIsNIL( nowSpace ) ) {
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (COND format) : " ) ;
    } // if
    
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 2 ) { 
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (COND format) : " ) ;
    } // if
    
    TreeType *returnTree = NULL ;
    if ( nowSpace->leftC->data.size() > 0 && 
         strcmp( nowSpace->leftC->data[0].lexical, "else" ) == 0 ) {
      for ( int i = 1 ; i < childTreeNum ; i++ ) {
        nowSpace = nowSpace->rightC ;
        EvalSymbol( nowSpace->leftC, returnTree, false ) ;
      } // for

    } // if
    else {
      returnTree = SubTreeResult( nowSpace ) ;
    } // else
    
    return returnTree ;
  } // GetElseResult()

  bool AllSubTreeWasTrue( TreeType *nowSpace ) {
    int childTreeNum = CountChiledTree( nowSpace ) ;
    for ( int i = 0 ; i < childTreeNum ; i++ ) {
      if ( CountChiledTree( nowSpace->leftC ) < 2 ) {
        m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
        throw ( "ERROR (COND format) : " ) ;
      } // if
        
      nowSpace = nowSpace->rightC ;
    } // for
    
    return true ;
  } // AllSubTreeWasTrue()

  bool DoCond( TreeType *nowSpace, TreeTypePointer &outSpace ) {
    outSpace = NULL ;
    int childTreeNum = CountChiledTree( nowSpace ) ;
    if ( childTreeNum < 1 ) { 
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (COND format) : " ) ;
      return false ;
    } // if
     
    AllSubTreeWasTrue( nowSpace ) ;
    for ( int i = 1 ; i < childTreeNum ; i++ ) {
      outSpace = SubTreeResult( nowSpace->leftC ) ;
      if ( outSpace != NULL ) {
        return true ;
      } // if
      
      nowSpace = nowSpace->rightC ;
    } // for
    
    if ( childTreeNum == 1 ) {
      outSpace = SubTreeResult( nowSpace->leftC ) ;
    } // if
    else {
      outSpace = GetElseResult( nowSpace->leftC ) ;
    } // else
    
    if ( outSpace == NULL ) {
      m_ErrorMsgTreeRoot = m_ErrorMsgIfCond ;
      throw ( "ERROR (no return value) : " ) ;
      return false;
    } // if
    else
      return true ;
  } // DoCond()
  
  bool DoClean() {
    m_defineSymbolList.clear() ;
    CreateDefineSymbolList() ;
    cout << "environment cleaned\n" ;
    return true ;
  } // DoClean()
  // num6
  // num7
  bool DoExit() {

    throw ( "ERROR (incorrect number of arguments) : exit" ) ;

    return false ;
  } // DoExit()
  
  vector<CharToken> GetTrueSYM( string inSYM ) { // 得到該SYMBOL的真實指令 
    TreeType *symTree = NULL ;
    for ( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
      if ( m_defineSymbolList[i].symbolName == inSYM ) {
        symTree = m_defineSymbolList[i].treeData ;
      } // if
    } // for

    if ( symTree == NULL )
      throw ( "ERROR (non-list) : " ) ;
    return symTree->data ;
  } // GetTrueSYM()
  
  bool IsNeedTopS( TreeType *leftChildSpace, string &needTopError ) { 
    // 要輸入左節點(放指令的) 是不是要在TOP的指令 'clean-environment' or 'define' or　'exit'

    vector<CharToken> trueData = GetTrueSYM( ChangeCharToStr( leftChildSpace->data[0].lexical ) ) ;

    if ( strcmp( trueData[0].lexical, "#<procedure exit>" ) == 0 ) {
      needTopError = "EXIT)" ;
      return true ;
    } // if
    else if ( strcmp( trueData[0].lexical, "#<procedure clean-environment>" ) == 0 ) {
      needTopError = "CLEAN-ENVIRONMENT)" ;
      return true ;
    } // else if
    else if ( strcmp( trueData[0].lexical, "#<procedure define>" ) == 0 ) {
      needTopError = "DEFINE)" ;
      return true ;
    } // else if
    
    return false ;
  } // IsNeedTopS()
  
  bool IsNeedFormatChack( TreeType *leftChildSpace ) { 
    // is 'define' or 'set!' or 'let' or 'cond' or 'lambda'
    vector<CharToken> trueData = GetTrueSYM( ChangeCharToStr( leftChildSpace->data[0].lexical ) ) ;

    if ( strcmp( trueData[0].lexical, "#<procedure define>" ) == 0 ) {
      return true ;
    } // if
    else if ( strcmp( trueData[0].lexical, "#<procedure set!>" ) == 0 ) {
      return true ;
    } // else if
    else if ( strcmp( trueData[0].lexical, "#<procedure let>" ) == 0 ) {
      return true ;
    } // else if
    else if ( strcmp( trueData[0].lexical, "#<procedure cond>" ) == 0 ) {
      return true ;
    } // else if
    else if ( strcmp( trueData[0].lexical, "#<procedure lambda>" ) == 0 ) {
      return true ;
    } // else if
    
    return false ;
  } // IsNeedFormatChack()
  
  bool IsIfAndOr( TreeType *leftChildSpace ) { // IfAndOr

    vector<CharToken> trueData = GetTrueSYM( ChangeCharToStr( leftChildSpace->data[0].lexical ) ) ;

    if ( strcmp( trueData[0].lexical, "#<procedure if>" ) == 0 ) {
      return true ;
    } // if
    else if ( strcmp( trueData[0].lexical, "#<procedure and>" ) == 0 ) {
      return true ;
    } // else if
    else if ( strcmp( trueData[0].lexical, "#<procedure or>" ) == 0 ) {
      return true ;
    } // else if
    
    return false ;
  } // IsIfAndOr()
  
  TreeType *GetDefineSymbolTree( string inSymbol ) { // 回傳定義symbol的位置 
    TreeType *outPlace = NULL ;
    for ( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
      if ( inSymbol == m_defineSymbolList[i].symbolName ) {
        outPlace = m_defineSymbolList[i].treeData ;
      } // if
          
    } // for
    
    
    return outPlace ;
  } // GetDefineSymbolTree()  

  TreeType *ReturnDefineSymbolToken( TreeType *inDefineToken ) { // 從type為11的指令token轉回type為10的token
     // cout << "inRE\n" ;
    TreeType *outTreeToken = new TreeType ;
    CharToken outToken ;
    outToken.type = 10 ;
    outTreeToken->leftC = NULL ;
    outTreeToken->rightC = NULL ;
    for ( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
      if ( inDefineToken == m_defineSymbolList[i].treeData ) {
         // cout << "got symbol\n" ;
        strcpy( outToken.lexical, m_defineSymbolList[i].symbolName.c_str() ) ;
      } // if
    } // for
     
    outTreeToken->data.push_back( outToken ) ;
    // cout << "outRE\n" ;
    return outTreeToken ;
  } // ReturnDefineSymbolToken()

  bool EvalSymbol( TreeType *nowSpace, TreeTypePointer &outSpace, bool isTop ) {
    m_ErrorMsgTreeRoot = nowSpace ;
    if ( nowSpace -> data.size() > 0 ) { // 當前節點不是空的，表示沒有子節點了 
      
      if ( nowSpace -> data[0].type == 10 ) { // 如果是symbol，去定義的list找 (m_defineSymbolList) LINE442
        
        if ( IsInDefineSymbolList( ChangeCharToStr( nowSpace -> data[0].lexical ) ) ) {
            // 在define symbol中 回傳定義的位置 
          outSpace = GetDefineSymbolTree( ChangeCharToStr( nowSpace -> data[0].lexical ) ) ; 
          return true ;
        } // if
        else {
          // 不在degine symbol, 為定義的symbol
          // string errorMsg = CharToString( nowSpace ) ;
          m_ErrorMsgTreeRoot = nowSpace ;
          throw ( "ERROR (unbound symbol) : " ) ;
          return false ;
        } // else
        
      } // if
      else { // 是其他atom
        outSpace = nowSpace ; // 傳回atom位置 
        return true ; 
      } // else
      
    } // if
    else {  // 當前節點是空的 
      
      if ( nowSpace->leftC->data.size() == 0 ) { // 求出左邊子樹的結果 
        TreeType *outSpaceLeft = NULL ;
        EvalSymbol( nowSpace->leftC, outSpaceLeft, false ) ;
        // cout << "End one!\n" ;
        TreeType *newNowSpace = new TreeType ;
        // cout << outSpaceLeft->data[0].lexical << endl ;
        // cout << "1\n" ;
        // 06_07改 
        if ( outSpaceLeft->data.size() > 0 && outSpaceLeft->data[0].type == 11 )
          newNowSpace->leftC = ReturnDefineSymbolToken( outSpaceLeft ) ;
        
        else { // 不是SYMBOL也不是QUOTE開頭 是atom  06_07改 
          m_ErrorMsgTreeRoot = outSpaceLeft ;
          throw ( "ERROR (attempt to apply non-function) : " ) ;
          return false ;
        } // else
        
        /*  
        else
          newNowSpace->leftC = outSpaceLeft ;
        */ 
        
        // cout << newNowSpace->leftC->data[0].lexical << endl ;
        // cout << "2\n" ;
        newNowSpace->rightC = nowSpace -> rightC ;
        // cout << "Go Two\n" ;
        EvalSymbol( newNowSpace, outSpace, isTop ) ;
        // cout << "End Two\n" ;
        return true ;
      } // if
           
      else if ( nowSpace->leftC->data[0].type == 6 ) { // 是QUOTE 
        DoQuote( nowSpace->rightC, outSpace ) ;
        return true ;
      } // else if

      else if ( !TheEndIsNIL( nowSpace ) ) { // 如果不是一個pure list
        vector<CharToken> trueData = GetTrueSYM( ChangeCharToStr( nowSpace -> leftC->data[0].lexical ) ) ;
        if ( strcmp( trueData[0].lexical, "#<procedure quote>" ) == 0 ) { // QUOTE建樹的時候好像有問題如果卡隱藏要檢查 
          DoQuote( nowSpace->rightC->leftC, outSpace ) ;
          return true ;
        } // if
        else {
          throw ( "ERROR (non-list) : " ) ;
          return false ;
        } // else

      } // if

      else if ( nowSpace->leftC->data[0].type == 10 ) {
        // cout << nowSpace->leftC->data[0].lexical << endl ;
        if ( IsInDefineSymbolList( ChangeCharToStr( nowSpace -> leftC -> data[0].lexical ) ) ) {
          string needTopError ;
          if ( IsNeedTopS( nowSpace -> leftC, needTopError ) && !isTop ) { 
            // 'clean-environment' or 'define' or 'exit'
            throw ( "ERROR (level of " + needTopError ) ;
            return false ;
          } // if

          if ( IsNeedFormatChack( nowSpace -> leftC ) ) { 
            // is 'define' or 'set!' or 'let' or 'cond' or 'lambda'
            // check format
            // evaluate
            // return result
            vector<CharToken> trueData = 
            GetTrueSYM( ChangeCharToStr( nowSpace -> leftC->data[0].lexical ) ) ;

            if ( strcmp( trueData[0].lexical, "#<procedure define>" ) == 0 ) {
              DoDefine( nowSpace->rightC ) ;
              return true ;
            } // if
            else if ( strcmp( trueData[0].lexical, "#<procedure cond>" ) == 0 ) {
              m_ErrorMsgIfCond = nowSpace ;
              DoCond( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if

          } // else if
          else if ( IsIfAndOr( nowSpace -> leftC ) ) { // if and or
            // check num of arguments 
            // evaluate
            // return result
            vector<CharToken> trueData = 
            GetTrueSYM( ChangeCharToStr( nowSpace -> leftC->data[0].lexical ) ) ;

            if ( strcmp( trueData[0].lexical, "#<procedure and>" ) == 0 ) {
              IsAnd( nowSpace->rightC, outSpace ) ;
              return true ;
            } // if
            else if ( strcmp( trueData[0].lexical, "#<procedure if>" ) == 0 ) {
              m_ErrorMsgIfCond = nowSpace ;
              DoIf( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure or>" ) == 0 ) {
              IsOr( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
          } // else if
          else { // not 'define' nor 'let' nor 'cond' nor 'lambda' 也不是 if and or??
            // check num of arguments 
            // evaluate
            vector<CharToken> trueData = 
            GetTrueSYM( ChangeCharToStr( nowSpace -> leftC->data[0].lexical ) ) ;
            
            /*
            if ( trueData[0].type != 11 ) {
              
            } // if
            */
            
            if ( strcmp( trueData[0].lexical, "#<procedure quote>" ) == 0 ) { 
              // QUOTE建樹的時候好像有問題如果卡隱藏要檢查 
              DoQuote( nowSpace->rightC->leftC, outSpace ) ;
              return true ;
            } // if

            if ( strcmp( trueData[0].lexical, "#<procedure cons>" ) == 0 ) {
              DoCons( nowSpace->rightC, outSpace ) ;
              return true ;
            } // if
            else if ( strcmp( trueData[0].lexical, "#<procedure list>" ) == 0 ) {
              DoList( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure car>" ) == 0 ) {
              DoCar( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure cdr>" ) == 0 ) {
              DoCdr( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure atom?>" ) == 0 ) {
              TreeIsAtom( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure pair?>" ) == 0 ) {
              TreeIsPair( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure list?>" ) == 0 ) {
              TreeIsList( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure null?>" ) == 0 ) {
              TreeIsNull( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure integer?>" ) == 0 ) {
              TreeIsInteger( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure real?>" ) == 0 ) {
              TreeIsReal( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure number?>" ) == 0 ) {
              TreeIsNumber( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure string?>" ) == 0 ) {
              TreeIsString( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure boolean?>" ) == 0 ) {
              TreeIsBoolean( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure symbol?>" ) == 0 ) {
              TreeIsSymbol( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure +>" ) == 0 ) {
              IsAdd( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure ->" ) == 0 ) {
              IsSub( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure *>" ) == 0 ) {
              IsMul( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure />" ) == 0 ) {
              IsDiv( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure not>" ) == 0 ) {
              IsNot( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure >>" ) == 0 ) {
              IsBigThan( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure >=>" ) == 0 ) {
              IsBigEqualThan( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure <>" ) == 0 ) {
              IsSmallThan( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure <=>" ) == 0 ) {
              IsSmallEqualThan( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure =>" ) == 0 ) {
              IsEqualThan( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure string-append>" ) == 0 ) {
              IsStringAppend( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure string>?>" ) == 0 ) {
              IsStringBig( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure string<?>" ) == 0 ) {
              IsStringSmall( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure string=?>" ) == 0 ) {
              IsStringEqual( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure eqv?>" ) == 0 ) {
              IsEqv( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure equal?>" ) == 0 ) {
              IsEqual( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure begin>" ) == 0 ) {
              DoBegin( nowSpace->rightC, outSpace ) ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure clean-environment>" ) == 0 ) {
              DoClean() ;
              return true ;
            } // else if
            else if ( strcmp( trueData[0].lexical, "#<procedure exit>" ) == 0 ) {
              DoExit() ;
              return true ;
            } // else if
            else {
    
              TreeType *errorOutTree = new TreeType ;
              for ( int i = 0 ; i < trueData.size() ; i++ )
                errorOutTree->data.push_back( trueData[i] ) ;
              errorOutTree->leftC = NULL ;
              errorOutTree->rightC = NULL ;
              m_ErrorMsgTreeRoot = errorOutTree ;
              throw ( "ERROR (attempt to apply non-function) : " ) ;
              return false ;
            } // else 

          } // else
        } // if
        else {
          m_ErrorMsgTreeRoot = nowSpace -> leftC ;
          throw ( "ERROR (unbound symbol) : " ) ;
          return false ;
        } // else
      } // else if

      else { // 不是SYMBOL也不是QUOTE開頭 是atom 
        m_ErrorMsgTreeRoot = nowSpace -> leftC ;
        throw ( "ERROR (attempt to apply non-function) : " ) ;
        return false ;
        
        /*
        outSpace = nowSpace ;
        return true ;
        */
      } // else if

    } // else

    return true ;
  } // EvalSymbol() 


  // ---------------------------------------------------P2
  
  public:
  Project2() {
      
    CreateDefineSymbolList() ;
    CreatePresetSymbolList() ;
  } // Project2()
  
  void TestP2() {
      // test m_defineSymbolList
    for ( int i = 0 ; i < m_defineSymbolList.size() ; i++ ) {
      cout << i << ".\t" << m_defineSymbolList[i].symbolName << " " ;
      TreeType *temp = m_defineSymbolList[i].treeData ;
      cout << temp->data[0].lexical << " " << temp->data[0].type << endl ;
    } // for
    
    // test IsNeedTopS
    TreeType *leftChildSpace = new TreeType ;
    CharToken tempT ;
    strcpy( tempT.lexical, "exit" ) ;
    leftChildSpace->data.push_back( tempT ) ;
    string tempStr ;
    if ( IsNeedTopS( leftChildSpace, tempStr ) )
      cout << "need!\n" ;
    else {
      cout << "don't need\n" ;
    } // else 
    
  } // TestP2()
  
  void TestDoP2( TreeType *nowSpace, TreeTypePointer &outSpace, bool isTop ) {
    m_treeRoot = nowSpace ;
    EvalSymbol( nowSpace, outSpace, true ) ;
  } // TestDoP2()

  TreeType *GetErrorTree() {
    return m_ErrorMsgTreeRoot ;
  } // GetErrorTree()
  
};





class Project1 {
  private:
  int m_nowLineNum ;
  int m_nowColumnNum ; 
  vector<CharToken> m_tokenLine ;
  TreeType *m_root ;
      
  char GetTheNextChar() {
    char outputChar ;
    m_nowColumnNum++ ;
    int isEOF = ( outputChar = cin.get() ) ;
    if ( isEOF == EOF ) {
      // cout << "fuck YOU I got EOF!!!!!!\n" ;
      throw "ERROR (no more input) : END-OF-FILE encountered" ;
      return -1 ;
    } // if 
      
    if ( outputChar == '\n' ) {
      m_nowLineNum++ ;
      m_nowColumnNum = 0 ;
    } // if
    
    // cout << "\ntest input:" << outputChar << " ; m_nowColumnNum:" << m_nowColumnNum << endl ;
    return outputChar ;
  } // GetTheNextChar()

  bool IsWhiteSpace( char input ) {
    if ( input == ' ' || input == '\n' || input == '\t' ) 
      return true ;
    return false ;
  } // IsWhiteSpace()

  char GetTheNextNonWhiteSpaceChar() {
    char tempChar = GetTheNextChar() ;
    char theNextChar ;
    while ( IsWhiteSpace( tempChar ) ) {
      tempChar = GetTheNextChar() ;
    } // while()
      
    return tempChar ;      // 回傳正常非空白 
  } // GetTheNextNonWhiteSpaceChar()
    
  bool GetStringToken( char outChar[100] ) { // 如果出現換行時還沒結束就回傳錯誤 
    char nextChar = '\0' ;
    char nowChar = '\0' ;
    int i = 0 ;
    nowChar = cin.peek() ;
    if ( nowChar != '\"' && nowChar != '\n' && nowChar != -1 ) {
      nowChar = GetTheNextChar() ;
      outChar[i] = nowChar ;
      nextChar = cin.peek() ;
      i++ ;
    } // if
    else if ( nowChar == '\"' ) {
      return true ;
    } // if
    else if ( nowChar == '\n' || nowChar != -1 ) {
      throw "ERROR (no closing quote) : END-OF-LINE encountered " ;
      return false ;
    } // else if 


    while ( nowChar == '\\' || ( nextChar != '\"' && nextChar != '\n' && nextChar != -1 ) ) {
      nowChar = GetTheNextChar() ;
      outChar[i] = nowChar ;
      nextChar = cin.peek() ;
      i++ ;
    } // while
    
    
    
    if ( nextChar == '\"' ) {
      return true ;
    } // if
    else if ( nextChar == '\n' || nextChar != -1 ) {
      throw "ERROR (no closing quote) : END-OF-LINE encountered " ;
      return false ;
    } // else if 
    
    return false ;
  } // GetStringToken()
    
  bool GetToken( char outChar[100] ) { // 單純切字串而已  
    // 單純切字串而已 
    // 如果下一個是 white-spaces, (, ), ', ", ;就切  
    char nextChar ;
    char nowChar = GetTheNextNonWhiteSpaceChar() ;
    if ( nowChar == '(' ) { // 假如讀到 '(' 就看下一個是不是 ')' 是就讀 不是就切 
      nextChar = GetTheNextNonWhiteSpaceChar() ;
      if ( nextChar == ')' ) {
        outChar[0] = '(' ;
        outChar[1] = ')' ;
        return true ;
      } // if
      else {
        outChar[0] = '(' ;
        cin.putback( nextChar ) ;
        m_nowColumnNum-- ;
        return true ;
      } // else
    
    }  // if 
    
    else if ( nowChar == ')' || nowChar == '\'' || nowChar == '\"' ) { // 判斷是不是斷點的符號 是就回傳 
      outChar[0] = nowChar ;
      return true ;
    } // else if
    
    else if ( nowChar == ';' ) { // 假如是 ';' 就讀到換行 去掉註解 
      outChar[0] = nowChar ;
      while ( nowChar != '\n' ) {
        nowChar = GetTheNextChar() ;
      } // while
      
      if ( GetToken( outChar ) ) // 跳過註解後 讀到下一個 
        return true ;
    } // else if
    
    else { // 讀一般TOKEN 
      outChar[0] = nowChar ;
      int i = 1 ;
      while ( cin.peek() != ')' && cin.peek() != '\'' && cin.peek() != '\"' && !IsWhiteSpace( cin.peek() ) &&
              cin.peek() != '(' && cin.peek() != ';' ) {
        outChar[i] = GetTheNextChar() ;
        i++ ;
      } // while
    
      return true ;
    } // else if
    
    // cout << "!!!false!!!" ;
    return false ;
  } // GetToken()

  bool IsDigit( char inChar ) {
    if ( '0' <= inChar && inChar <= '9' ) 
      return true ;
    return false ;
  } // IsDigit()

  bool IsDigitOrDot( char inChar ) {
    if ( ( '0' <= inChar && inChar <= '9' ) || inChar == '.' ) 
      return true ;
    return false ;
  } // IsDigitOrDot()

  bool CheckLP( char inChar[100] ) {
    if ( strcmp( inChar, "(" ) == 0 ) 
      return true ;
    return false ;
  } // CheckLP()
  
  bool CheckRP( char inChar[100] ) {
    if ( strcmp( inChar, ")" ) == 0 )
      return true ;
    return false ;
  } // CheckRP()
  
  bool CheckInt( char inChar[100] ) {
    int i = 0 ;
    int countDigit = 0 ;
    if ( inChar[i] == '+' || inChar[i] == '-' ) {
      i = 1 ;
    } // if
    
    for ( ; i < strlen( inChar ) ; i++ ) {
      if ( inChar[i] >= '0' && inChar[i] <= '9' ) {
        countDigit++ ;
      } // if
      
      if ( !IsDigit( inChar[i] ) ) {
        return false ;
      } // if
      
    } // for
    
    if ( countDigit == 0 )
      return false ;
    return true ;
  } // CheckInt()
  
  bool CheckString( char inChar[100] ) {
    if ( strcmp( inChar, "\"" ) == 0 )
      return true ;
    return false ;
  } // CheckString()
  
  bool CheckDot( char inChar[100] ) {
    if ( strcmp( inChar, "." ) == 0 )
      return true ;
    return false ;
  } // CheckDot()
  
  bool CheckFloat( char inChar[100] ) {
    int countDot = 0 ;
    int countDigit = 0 ;
    int i = 0 ;
    if ( inChar[i] == '+' || inChar[i] == '-' ) {
      i = 1 ;
    } // if
    
    for ( ; i < strlen( inChar ) ; i++ ) {
      if ( !IsDigitOrDot( inChar[i] )  ) {
        return false ;
      } // if
      
      if ( inChar[i] >= '0' && inChar[i] <= '9' ) {
        countDigit++ ;
      } // if
      
      if ( inChar[i] == '.' ) {
        countDot++ ;
      } // if
      
    } // for
    
    
    if ( countDot == 1 && countDigit > 0 )
      return true ;
    
    return false ;
  } // CheckFloat()
  
  bool CheckNIL( char inChar[100] ) {
    if ( strcmp( inChar, "nil" ) == 0 || strcmp( inChar, "#f" ) == 0 || strcmp( inChar, "()" ) == 0 )
      return true ;
    return false ;
  } // CheckNIL()
  
  bool CheckT( char inChar[100] ) {
    if ( strcmp( inChar, "t" ) == 0 || strcmp( inChar, "#t" ) == 0 )
      return true ;
    return false ;
  } // CheckT()
  
  bool CheckQuote( char inChar[100] ) {
      
    if ( strcmp( inChar, "\'" ) == 0 ) 
      return true ;
    
    return false ;
  } // CheckQuote()
  
  bool CheckSymbol( char inChar[100] ) {
    return true ;
  } // CheckSymbol()

    // LP     : 1   RP     : 2
    // Dot    : 3   NIL    : 4
    // T      : 5   Quote  : 6
    // Int    : 7   Float  : 8
    // String : 9   Symbol : 10   
  int CheckType( char inChar[100] ) {  
    if ( CheckLP( inChar ) ) {
      return 1 ;
    } // if
    else if ( CheckRP( inChar ) ) {
      return 2 ;
    } // else if
    else if ( CheckDot( inChar ) ) {
      return 3 ;
    } // else if
    else if ( CheckNIL( inChar ) ) {
      return 4 ;
    } // else if
    else if ( CheckT( inChar ) ) {
      return 5 ;
    } // else if
    else if ( CheckQuote( inChar ) ) {
      return 6 ;
    } // else if
    else if ( CheckInt( inChar ) ) {
      return 7 ;
    } // else if
    else if ( CheckFloat( inChar ) ) {
      return 8 ;
    } // else if
    else if ( CheckString( inChar ) ) {
      return 9 ;
    } // else if
    else if ( CheckSymbol( inChar ) ) {
      return 10 ;
    } // else if

        
    return 0 ;
  } // CheckType()

  bool GetCharToken( CharToken &outToken, char errorChar[100] ) {  // 得到字串和種類 
    char newChar[100] = {0} ;
    if ( GetToken( newChar ) ) {
      int type = CheckType( newChar ) ;
      if ( type != 0 ) {
        strcpy( outToken.lexical, newChar ) ;
        outToken.type = type ;
        return true ;
      } // if
      else {
        strcpy( errorChar, newChar ) ;
        return false ;
      } // else
      
    } // if
    
    return false ;
  } // GetCharToken()

  bool GetString( CharToken &outToken ) {  // 得到字串和種類  
    char newChar[100] = {0} ;
    if ( GetStringToken( newChar ) ) {
      strcpy( outToken.lexical, newChar ) ;
      outToken.type = 9 ;
      return true ;
    } // if
    
    return false ;
  } // GetString()
 
    // LP     : 1   RP     : 2
    // Dot    : 3   NIL    : 4
    // T      : 5   Quote  : 6
    // Int    : 7   Float  : 8
    // String : 9   Symbol : 10   
  bool IsS_exp( CharToken inToken, char errorToken[100] ) {
    // 先讀一個 判斷是不是 "(" 或 "\'" 
    // 
    
    if ( inToken.type == 1 ) { // 判斷是不是"(" 
      m_tokenLine.push_back( inToken ) ; // 再讀一個 
      if ( GetCharToken( inToken, errorToken ) ) { // 判斷是不是EXP 
        if ( !IsS_exp( inToken, errorToken ) ) { 
          // cout << "error1" ;
          throw "ERROR (unexpected token) : atom or '(' expected " ;
          return false ;      
        } // if
        
        GetCharToken( inToken, errorToken ) ; // 再讀一個  
        while ( inToken.type != 3 && inToken.type != 2 ) {
          if ( !IsS_exp( inToken, errorToken ) ) {
            // cout << "error2" ;
            throw "ERROR (unexpected token) : atom or '(' expected " ;
            return false ;
          } // if
          
          GetCharToken( inToken, errorToken ) ;
        } // while
        
        if ( inToken.type == 3 ) {
          m_tokenLine.push_back( inToken ) ;
          GetCharToken( inToken, errorToken ) ;
          if ( !IsS_exp( inToken, errorToken ) ) {
            throw "ERROR (unexpected token) : atom or '(' expected " ;
            // cout << "error3" ;
            return false ;
          } // if
          
          
          GetCharToken( inToken, errorToken ) ;
        } // if
        
        if ( inToken.type == 2 ) {
          m_tokenLine.push_back( inToken ) ;
          return true ; 
        } // if
        else {
          strcpy( errorToken, inToken.lexical ) ;
          throw "ERROR (unexpected token) : ')' expected " ;
          return false ;
        } // else
      } // if
      else {
        cout << "error?1" << endl ;
        return false ;
      } // else
        
    } // if
    else if ( inToken.type == 6 ) {
      m_tokenLine.push_back( inToken ) ;
      GetCharToken( inToken, errorToken ) ;
      if ( IsS_exp( inToken, errorToken ) ) {
        return true ;
      } // if 
      
    } // else if
    else {
      if ( IsATOM( inToken, errorToken ) ) 
        return true ;
      else
        throw "ERROR (unexpected token) : atom or '(' expected " ;
    } // else
    
    return false ;
  } // IsS_exp()

  bool IsATOM( CharToken inToken, char errorToken[100] ) {
    if ( inToken.type == 9 ) {
      m_tokenLine.push_back( inToken ) ;
      if ( GetString( inToken ) ) {
        m_tokenLine.push_back( inToken ) ;
        GetCharToken( inToken, errorToken ) ;
        m_tokenLine.push_back( inToken ) ;
        return true ;
      } // if
      else {
        strcpy( errorToken, "\n" ) ;
        return false ;
      } // else
      
    } // if
    else if ( inToken.type != 1 && inToken.type != 2 &&
              inToken.type != 3 && inToken.type != 6 ) {
      m_tokenLine.push_back( inToken ) ;
      return true ;
    } // else if
    
    if ( inToken.type == 1 ) strcpy( errorToken, "(" ) ;
    if ( inToken.type == 2 ) strcpy( errorToken, ")" ) ;
    if ( inToken.type == 3 ) strcpy( errorToken, "." ) ;
    if ( inToken.type == 6 ) strcpy( errorToken, "\'" ) ;
    
    return false ;
  } // IsATOM()

  bool InitialTreeToken( TreeType *inTree ) {
    inTree->data.clear() ;
    inTree->leftC = NULL ;
    inTree->rightC = NULL ;
    return true ;
  } // InitialTreeToken()

  // 4/12更: 建樹要檢查, 以下是出現問題的式子 
  /*
  ((1 2 3)
   (4 . 5) 
   . 
   (6 (7 . nil) 
      (8 . 9)
   )
  ) 
  ((1 2 3) (4 . 5) . (6 (7 . nil) (8 . 9)))   
  */

  bool GetExpUntilDotOrRP( int &nowTokenNum, TreeType *inTreePlace ) {
    TreeType *nowTreePlace = inTreePlace ;
    if ( m_tokenLine[nowTokenNum].type != 2 && m_tokenLine[nowTokenNum].type != 3 ) {
      // 如果遇到的不是右括號或點
      // 往右建一個新節點 
      // 在往左建一個新節點 
      // 建樹 
      // 往右建一個新的節點
      // 建右樹 
      TreeType *nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->rightC = nextTree ;
      nowTreePlace = nextTree ;
      nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->leftC = nextTree ;
      StartExpTree( nowTokenNum, nextTree ) ;
      /*
      nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->rightC = nextTree ;
      */
      GetExpUntilDotOrRP( nowTokenNum, nowTreePlace ) ;
      // cout << "End Right!\n" ;
      return true ;
    } // if
    else if ( m_tokenLine[nowTokenNum].type == 3 ) {
      // 如果遇到的是點 
      // 就往右建節點 
      // 直接建樹 
      // 最後跳過右括號 
      // 
      //
      nowTokenNum++ ; // 跳過DOT 
      TreeType *nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->rightC = nextTree ;
      StartExpTree( nowTokenNum, nextTree ) ; // 取得DOT後的EXP 
      nowTokenNum++ ; // 跳過左括號
      // cout << "End Right Dot!\n" ;  
      return true ;
    } // else if
    
    else if ( m_tokenLine[nowTokenNum].type == 2 ) {
      // 如果讀到右括號 
      // 跳過右括號 
      // 建一個新的節點放右邊 
      // 把他設成NIL 
      nowTokenNum++ ;
      TreeType *nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->rightC = nextTree ;
      CharToken nilToken ;
      strcpy( nilToken.lexical, "nil" ) ;
      nilToken.type = 4 ;
      nextTree->data.push_back( nilToken ) ;
      // cout << "End Right RP!\n" ;
      return true ; 
    } // else if
    
    return false ;
  } // GetExpUntilDotOrRP()

  bool StartExpTree( int &nowTokenNum, TreeType *inTreePlace ) {
    // 建樹 
    /*
    TreeType *nextTree = new TreeType ;
    InitialTreeToken( nextTree ) ;
    */
    TreeType *nowTreePlace = inTreePlace ;
    if ( m_tokenLine[nowTokenNum].type == 1 ) {
      // 假如是左括號 
      // 建出一個新的節點 
      // 然後進左邊
      // 去做右邊 (傳過去的位置是當前的位置)
      //         
      nowTokenNum++ ;
      TreeType *nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->leftC = nextTree ;
      StartExpTree( nowTokenNum, nextTree ) ;
      GetExpUntilDotOrRP( nowTokenNum, nowTreePlace ) ;   
      return true ;
        // --------------
    } // if ( m_tokenLine[nowTokenNum].type == '(' )
     
    else if ( m_tokenLine[nowTokenNum].type == 6 ) {
      // 如果是quote就存在當前這個
      // 建出一個新的節點
      // 進左邊
      TreeType *nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nextTree->data.push_back( m_tokenLine[nowTokenNum] ) ;
      nowTokenNum++ ;
      nowTreePlace->leftC = nextTree ;
      nextTree = new TreeType ;
      InitialTreeToken( nextTree ) ;
      nowTreePlace->rightC = nextTree ;
      StartExpTree( nowTokenNum, nextTree ) ; 
      return true ;
    } // else if( m_tokenLine[nowTokenNum].type == '\'' )
    
    else if ( m_tokenLine[nowTokenNum].type == 9 ) { // is String
      nowTreePlace->data.push_back( m_tokenLine[nowTokenNum] ) ;
      // cout << nowTreePlace->data[0].type ; // test
      nowTokenNum++ ;
      nowTreePlace->data.push_back( m_tokenLine[nowTokenNum] ) ;
      // cout << nowTreePlace->data[1].type ; // test
      nowTokenNum++ ;
      nowTreePlace->data.push_back( m_tokenLine[nowTokenNum] ) ;
      // cout << nowTreePlace->data[2].type << endl ; // test
      nowTokenNum++ ;
      return true ;      
    } // else if String
    else {
      nowTreePlace->data.push_back( m_tokenLine[nowTokenNum] ) ;
      // cout << nowTreePlace->data[0].type << endl ; // test
      nowTokenNum++ ;
      return true ;
    } // else is atom
    
    return false ;
  } // StartExpTree()

  bool CreateParseTree() { // -------------------!!!! 要解決樹葉兩端都是NIL (4/12更: 好像不用?)!!!!-------------------
    m_root = new TreeType ;
    InitialTreeToken( m_root ) ;
    int nowTokenNum = 0 ;
    StartExpTree( nowTokenNum, m_root ) ;
    return true ;
  } // CreateParseTree()

  void PrintStringType( CharToken inToken ) {
    for ( int i = 0 ; i < strlen( inToken.lexical ) ; i++ ) {
      if ( inToken.lexical[i] == '\\' ) {
        if ( i+1 < strlen( inToken.lexical ) && inToken.lexical[i+1] == '\\' ) {
          i++ ; // 跳過 '\' 
          cout << inToken.lexical[i] ;
        } // if
        else if ( i+1 < strlen( inToken.lexical ) && inToken.lexical[i+1] == '\"' ) {
          i++ ; // 跳過 '\' 
          cout << inToken.lexical[i] ;
        } // if
        else if ( i+1 < strlen( inToken.lexical ) && inToken.lexical[i+1] == 'n' ) {
          i++ ; // 跳過 '\'
          cout << '\n' ;
        } // if
        else if ( i+1 < strlen( inToken.lexical ) && inToken.lexical[i+1] == 't' ) {
          i++ ; // 跳過 '\' 
          cout << '\t' ;
        } // if
        else {
          cout << inToken.lexical[i] ;
        } // else
      } // if
      else {
        cout << inToken.lexical[i] ;
      } // else
    } // for
  } // PrintStringType()

  void PrintNilType( CharToken inToken ) {
    cout << "nil" ;
  } // PrintNilType()
  
  void PrintTrueType( CharToken inToken ) {
    cout << "#t" ;
  } // PrintTrueType()
  
  void PrintIntType( CharToken inToken ) {
    int outInt = atoi( inToken.lexical ) ;
    cout << outInt ;
  } // PrintIntType()

  void PrintFloatType( CharToken inToken ) {
    float outFloat = atof( inToken.lexical ) ;
    cout << fixed << setprecision( 3 ) << outFloat ;
  } // PrintFloatType()

  void PrintSymbolType( CharToken inToken ) {
    cout << inToken.lexical ;
  } // PrintSymbolType()

  void PrintQuoteType( CharToken inToken ) {
    cout << "quote" ;
  } // PrintQuoteType()
 
    // LP     : 1   RP     : 2
    // Dot    : 3   NIL    : 4
    // T      : 5   Quote  : 6
    // Int    : 7   Float  : 8
    // String : 9   Symbol : 10     
  void PrintLeave( TreeType *nowSpace ) { // 沒有用到!! 
    if ( nowSpace->data.size() != 0 ) {
      for ( int i = 0 ; i < nowSpace->data.size() ; i++ ) {
        if ( nowSpace->data[i].type == 9 ) {
          PrintStringType( nowSpace->data[i] ) ;
        } // if
        else if ( nowSpace->data[i].type == 10 ) {
          PrintSymbolType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 8 ) {
          PrintFloatType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 7 ) {
          PrintIntType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 6 ) {
          PrintQuoteType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 5 ) {
          PrintTrueType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 4 ) {
          PrintNilType( nowSpace->data[i] ) ;
        } // else if
        else {
          PrintStringType( nowSpace->data[i] ) ;
        } // else 
        
      } // for
      
      cout << endl ;
    } // if

    
    if ( nowSpace->leftC != NULL ) {
      cout << "-----------go Left\n";
      PrintLeave( nowSpace->leftC ) ;
      cout << "-----------back Left\n";
    } // if
    
    if ( nowSpace->rightC != NULL ) {
      cout << "-----------go Right\n";
      PrintLeave( nowSpace->rightC ) ;
      cout << "-----------back Right\n";
    } // if 
    
  } // PrintLeave()

  bool ThatChildIsNIL( TreeType *nowSpace ) {
    if ( nowSpace->data.size() != 0 && nowSpace->data[0].type == 4 ) {
      return true ;
    } // if
    
    return false ;
  } // ThatChildIsNIL()

  bool ThatChildDosen_tHaveChild( TreeType *nowSpace ) {
    if ( nowSpace->leftC == NULL && nowSpace->rightC == NULL )
      return true ;
        
    return false ;
  } // ThatChildDosen_tHaveChild()

  void PrintLeaveEnd( TreeType *nowSpace, int spaceNum, char nowSide[20] ) {
    char nextSide[20] ;
    bool hasQ = false ;
    if ( nowSpace->data.size() == 0 ) { // 假設當前節點是空的 
      if ( strcmp( nowSide, "left" ) == 0 ) { // 假如現在是在左子樹 
        cout << "( " ;
        spaceNum = spaceNum + 2 ;
      } // if

      if ( nowSpace->leftC->data.size() > 0 && 
           nowSpace->leftC->data[0].type == 6 ) {
        cout << "quote\n" ;
        if ( nowSpace->rightC->data.size() == 0 ) // 2021_06_06改 (多這行) 
          hasQ = true ;          
          /*
          for ( int i = 0 ; i < spaceNum ; i++ )
            cout << " " ;
          
          */
      } // if
      else {
        strcpy( nextSide, "left" ) ;
        PrintLeaveEnd( nowSpace->leftC, spaceNum, nextSide ) ;          
      } // else

      if ( ThatChildIsNIL( nowSpace->rightC ) && 
           ( nowSpace->leftC->data.size() == 0 || nowSpace->leftC->data[0].type != 6 ) ) {
        spaceNum = spaceNum - 2 ; 
        for ( int i = 0 ; i < spaceNum ; i++ )
          cout << " " ;
      } // if
      else {
        for ( int i = 0 ; i < spaceNum ; i++ )
          cout << " " ;
        if ( hasQ ) {
          cout << "( " ;
          spaceNum = spaceNum + 2 ;
        } // if
          
        if ( ThatChildDosen_tHaveChild( nowSpace->rightC ) ) { 
          if ( nowSpace->leftC->data.size() != 0 && 
               nowSpace->leftC->data[0].type == 6 ) { // 2021_06_06改 (多這行) 
            ;
          } // if 2021_06_06改 (多這行) 
          else {
            cout << ".\n" ; 
            for ( int i = 0 ; i < spaceNum ; i++ )
              cout << " " ;
          } // else

          strcpy( nextSide, "right" ) ;
          PrintLeaveEnd( nowSpace->rightC, spaceNum, nextSide ) ;
          spaceNum = spaceNum - 2 ; 
          for ( int i = 0 ; i < spaceNum ; i++ )
            cout << " " ;
        } // if
        else {
          strcpy( nextSide, "right" ) ;
          PrintLeaveEnd( nowSpace->rightC, spaceNum, nextSide ) ;
          spaceNum = spaceNum - 2 ; 
          
        } // else
        
        if ( hasQ ) {
          /*
          spaceNum = spaceNum - 2 ;
          for ( int i = 0 ; i < spaceNum ; i++ )
            cout << "+" ;
          */
          cout << ")\n" ;
          spaceNum = spaceNum - 2 ;
          for ( int i = 0 ; i < spaceNum ; i++ )
            cout << " " ;
        } // if
      } // else
      
      if ( strcmp( nowSide, "left" ) == 0 ) {
        cout << ")\n" ;
      } // if
      
    } // if is notthing
    /*
    else if ( nowSpace->data[0].type == 6 ) {
      cout << "( quote\n" ;
      spaceNum = spaceNum + 2;
      for ( int i = 0 ; i < spaceNum ; i++ )
        cout << " " ;
      strcpy( nextSide, "left" ) ;
      PrintLeaveEnd( nowSpace->leftC, spaceNum, nextSide ) ;
      spaceNum = spaceNum - 2;
      for ( int i = 0 ; i < spaceNum ; i++ )
        cout << " " ;
      cout << ")\n" ;
    } // else if is '
    */
    else {
      for ( int i = 0 ; i < nowSpace->data.size() ; i++ ) {
        if ( nowSpace->data[i].type == 9 ) {
          PrintStringType( nowSpace->data[i] ) ;
        } // if
        else if ( nowSpace->data[i].type == 10 ) {
          PrintSymbolType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 8 ) {
          PrintFloatType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 7 ) {
          PrintIntType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 6 ) {
          PrintQuoteType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 5 ) {
          PrintTrueType( nowSpace->data[i] ) ;
        } // else if
        else if ( nowSpace->data[i].type == 4 ) {
          PrintNilType( nowSpace->data[i] ) ;
        } // else if
        else {
          PrintStringType( nowSpace->data[i] ) ;
        } // else 
      } // for
      
      cout << endl ;
    } // else
  } // PrintLeaveEnd()
  


  void PrettyPrint() { // jest fst test
    TreeType *nowSpace = m_root ;

    // PrintLeave( nowSpace ) ;
    char nextSide[20] ;
    strcpy( nextSide, "left" ) ;
    PrintLeaveEnd( nowSpace, 0, nextSide ) ;

  } // PrettyPrint()

  void PrintP2( TreeType *nowSpace ) {
    char nextSide[20] ;
    strcpy( nextSide, "left" ) ;
    PrintLeaveEnd( nowSpace, 0, nextSide ) ;
  } // PrintP2()



  void SkipEndLineWhitheSpace() {
    char nextChar[100] ;
    int i = 0 ;
    nextChar[i] = GetTheNextChar() ;
    i++ ;
    while ( nextChar[i-1] == ' ' || nextChar[i-1] == '\t' ) {
      nextChar[i] = GetTheNextChar() ;
      i++ ;
    } // while
    
    i-- ;
    if ( nextChar[i] != '\n' && nextChar[i] != ';' ) {
      while ( i >= 0 ) {
        cin.putback( nextChar[i] ) ;
        m_nowColumnNum-- ;
        i-- ;
      } // while
    } // if
    else if ( nextChar[i] == ';' ) {
      while ( nextChar[i] != '\n' ) {
        nextChar[i] = GetTheNextChar() ;
      } // while
    } // else if
    
  } // SkipEndLineWhitheSpace()

  bool CommandIsEnd() { // jest fst test
    if ( m_root != NULL ) {
      if ( m_root->data.size() == 0 ) {
        if ( m_root->leftC != NULL &&
             m_root->rightC != NULL ) {
          if ( m_root->leftC->data.size() == 1 &&
               m_root->rightC->data.size() == 1 ) {
            if ( strcmp( m_root->leftC->data[0].lexical, "exit" ) == 0 &&
                 m_root->rightC->data[0].type == 4 )
              return true ;
          } // if
        } // if 
      } // if
    } // if

    
    return false ;
  } // CommandIsEnd()

  void SkipErrorLine() {
    char unNeedChar = '\0' ;
    while ( unNeedChar != '\n' )
      unNeedChar = GetTheNextChar() ;
  } // SkipErrorLine()


  public:
  Project1() {
    m_nowLineNum = 1 ;
    m_nowColumnNum = 0 ; 
  } // Project1()

  
  void TestIsS_exp( char errorToken[100] ) {
    
    CharToken inToken ;
    cout << "Welcome to OurScheme!\n" ;
    cout << "\n> " ;
    // cout << "START: " ;
    GetCharToken( inToken, errorToken ) ;
    while ( IsS_exp( inToken, errorToken ) ) {
      if ( m_tokenLine.size() == 3 && 
           strcmp( m_tokenLine[0].lexical, "(" ) == 0 && 
           strcmp( m_tokenLine[1].lexical, "exit" ) == 0 && 
           strcmp( m_tokenLine[2].lexical, ")" ) == 0 ) {
        
        return ;
      } // if
      /*
      for ( int i = 0 ; i < m_tokenLine.size() ; i++ ) {
        cout << m_tokenLine[i].lexical << endl ;
      } // for
      */
      CreateParseTree() ;
      // cout << "Start Print!!!\n" ;
      PrettyPrint() ;
      // cout << "\nEnd Print!!!\n" ;
      m_tokenLine.clear() ;
      // cout << "?????" ;
      SkipEndLineWhitheSpace() ;
      m_nowColumnNum = 0 ;
      m_nowLineNum = 1 ;
      cout << "\n> " ;
      GetCharToken( inToken, errorToken ) ;
    } // while


  } // TestIsS_exp()



  bool DoingP1() {
    char errorToken[100] ;
    CharToken inToken ;
    cout << "Welcome to OurScheme!\n" ;
    // cout << "\n> " ;
    // cout << "START: " ;
    Project2 p2 = Project2() ; // create P2 *------------------
    while ( !CommandIsEnd() ) {
      try {
        cout << "\n> " ;
        m_tokenLine.clear() ;
        SkipEndLineWhitheSpace() ;
        m_nowColumnNum = 0 ;
        m_nowLineNum = 1 ;
        
        GetCharToken( inToken, errorToken ) ;
        IsS_exp( inToken, errorToken ) ;
        // cout << "Create Tree Start!\n" ;
        CreateParseTree() ;
        // cout << "Create Tree Clear!\n" ;
        if ( !CommandIsEnd() ) {
          // cout << "Print Tree Start!\n" ;
          // PrettyPrint() ;
          // ---------------------------------------------P2 TEST
          TreeType *outSpace = NULL ;
          try {
              
            p2.TestDoP2( m_root, outSpace, true ) ;
            if ( outSpace != NULL )
              PrintP2( outSpace ) ;
          } // try
          catch( const char * errormsg ) {

            if ( errormsg[7] == 'i' && errormsg[8] == 'n' ) {
              cout << errormsg << endl ;
            } // if
            else if ( errormsg[7] == 'd' && errormsg[8] == 'i' ) {
              cout << errormsg << endl ;
            } // else if
            else {
              cout << errormsg ;
              PrintP2( p2.GetErrorTree() ) ;
            } // else
                  
          }  // catch
          catch( string errorStr ) {
            cout << errorStr << endl ;
          } // catch
          
          // ---------------------------------------------P2 TEST
          // cout << "Print Tree Clear!\n" ;
        } // if
        else {
          cout << endl ;
        } // else
      } // try

      catch ( const char * msg ) {
        if ( strcmp( msg, "ERROR (unexpected token) : atom or '(' expected " ) == 0 ||
             strcmp( msg, "ERROR (unexpected token) : ')' expected " ) == 0 ) {
          // cout << "\n|||test||| " << GetColumn() << " " << strlen( errorToken ) << "\n" ; 
          cout << msg << "when token at Line " << GetLine() << " Column " << 
                  GetColumn() - strlen( errorToken ) + 1 << " is >>" << errorToken  << "<<\n" ;
          try {
            SkipErrorLine() ;
          } // try
          catch ( const char * msg ) {
            if ( strcmp( msg, "ERROR (no more input) : END-OF-FILE encountered" ) == 0 ) 
              cout << "\n> " << msg << endl ; // 06_06改 
            return false ;
          } // catch
          
          
        } // if
        
        else if ( strcmp( msg, "ERROR (no closing quote) : END-OF-LINE encountered " ) == 0 ) {
          cout << msg << "at Line " << GetLine() << " Column " << 
                  GetColumn() + 1 << endl ; // - strlen( errorToken ) 
          try {
            SkipErrorLine() ;
          } // try
          catch ( const char * msg ) {
            if ( strcmp( msg, "ERROR (no more input) : END-OF-FILE encountered" ) == 0 )
              cout << msg << endl ;
          } // catch
        } // if else
        
        else if ( strcmp( msg, "ERROR (no more input) : END-OF-FILE encountered" ) == 0 ) {
          // cout << "End HERE!!!!!!\n" ;
          cout << msg << endl ;
          throw "EOF ERROR" ;
          return false ;
        } // if else
        else {
          cout << msg << endl ;
        } // else
      } // catch

    } // while
    
    return true ;
  } // DoingP1()

  int GetLine() {
    return m_nowLineNum ;
  } // GetLine()
  
  int GetColumn() {
    return m_nowColumnNum ;
  } // GetColumn()


   
    
} ;
/*
// test Main
int main() {
    Project2 p2 = Project2() ;
    p2.testP2() ;
}
// test Main
*/
 // ======================== true Main =======================================
    
int main() {
  int dataNum ;
  cin >> dataNum ;
    
  char errorToken[100] ;

  try {
    Project1 p1 ;
    p1.DoingP1() ;
    cout << "Thanks for using OurScheme!" ;
  } // try
  catch ( const char * msg ) {

    // cout << "\n> ERROR (no more input) : END-OF-FILE encountered\n" ;
    cout << "Thanks for using OurScheme!" ;
  } // catch

} // main()
    
 // ======================== true Main =======================================

    



#ifndef __VS_XML_PARSER_NEW_H__
#define __VS_XML_PARSER_NEW_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


// 按1编译struct内存长度
#pragma pack(1)


/********************************************************************************
*                    重点提醒：TYPE_STRING 类型的长度,必须是4的倍数
********************************************************************************/

#define XML_TITLE		"<IPC>\r\n"

/* 定义分析结构体组成类型 */
enum field_types
{
    TYPE_STRUCT = 0,              // 结构体

    TYPE_INT,                      // 1   int
    TYPE_STRING,                   // 2   char *,   特别注意，长度必须为4的倍数，因为内存地址值必定是4的倍数.
    TYPE_BOOL,                     // 3   int,      针对xml中出现的 TRUE,FALSE 型
    TYPE_CHAR,                     // 4   char,     尽量不使用这个,用 char[4] + TYPE_STRING 配合使用保险些

    TYPE_IP_ADDR,                  // 5  unsigned long int,  IP型, 或者利用 char[16] + TYPE_STRING 配合使用更保险直观些

    TYPE_DATE_DT,                  // 6  这些时间....还有待分析
    TYPE_TIME_LDT,                 // 7
    TYPE_DATE_D,                   // 8
    TYPE_DATE_T,                   // 9
    TYPE_DATE_T2,                  // 10
};

enum err_xml_code
{
    XML_SUCCESS =               0,
    /* 如果返回错误时, 可能的错误代码 */
    XML_ERR_MEMORY =           1,    // 内存分配错误
    XML_ERR_ARRAY_LESS =      2,    // 结构体定义的数组太小,XML中的数组数据多于数组定义
    XML_ERR_NO_FIND_DESC =    4    // 没有找到该结构体描述,应该是_INDEX没有加到 enum sub_struct_index或find_sub_strcut_desc函数中未返回
};

/* 当struct转成xml格式时,一些显示方式定义 */
enum input_type
{
    HAVE_TITLE = 1,                     // 写明 <Message>这样的头
    NO_TITLE = 2,                       //   否
    
    EASY_CLOSE = 4,                     // 简易模式 <A .. />
    FULL_CLOSE = 8,                     // 前后匹配方式, <A> ... </A>

    LIST_SHOW = 16,                     // 列表显示 <A>1</A> <B>2<B>...
    ATTRIB_SHOW = 32,                   // 属性显示 <A a=1 b=2 />

    SHOW_INT_0 = 64,                    // 如果是int型,碰到0也认为是有效值(默认0无效)
    SHOW_STRING_NULL = 128,            // 如果是string型,碰到NULL也认为有效(默认NULL无效)

    TEST_MODE = NO_TITLE | ATTRIB_SHOW |SHOW_INT_0 | SHOW_STRING_NULL       // 测试用
};

/***********************************************************************
*          对结构体的解析。这是联接struct与xml之间的中转信息
***********************************************************************/
typedef struct tagFIELD_TYPE
{
    char name[50];                  // 字段名称
    int  size;                      // 字段大小
    int  type;                      // 字段类型: 需要总结.
    int  repeat;                    // 重复数,即数组长度 0,1,表示仅一位(默认0也表示有一位)
    int  only_struct_index;       // 根据find_sub_strcut_desc函数查找描述之索引,用于struct嵌套
}FIELD_TYPE, *PFIELD_TYPE;

/***********************************************************************
*          同样是对结构体的解析,描述struct的总体信息
*     此 INPUT_MESSAGE 与上一下 FIELD_TYPE 共同构成对struct的描述
***********************************************************************/
typedef struct tagINPUT_MESSAGE
{
    char name[50];                    // 协议标签头名称 通常都是 Message 吧
    int  input_fdarray_count;       // 输入的协议,数组数
    int  input_type;                 // 显示的方式, 比如 HAVE_TITLE|FULL_CLOSE|LIST_SHOW
}INPUT_MESSAGE, *PINPUT_MESSAGE;

/***********************************************************************
*                          特殊调用函数
***********************************************************************/
// 调用函数原型
char * find_sub_strcut_desc(int index, INPUT_MESSAGE *out_inputmsg);
// 函数别名
typedef char * __find_sub_strcut_desc(int index, INPUT_MESSAGE *out_inputmsg);

/***********************************************************************
*                        结构体复制函数
***********************************************************************/
char * malloc_struct(INPUT_MESSAGE *in_inputmsg, char *out_msg_buf, FIELD_TYPE * in_fdarray);


/***********************************************************************
*                          解析XML函数
***********************************************************************/
//int struct2xml_6091(alarmConfig_Req alarmConfig, char *outbuf);

// 将xml解析成struct结构.最后一个参数fun是函数,与struct_index相匹配的函数
int xml2struct( char *xml_string, int xml_len, char *outbuf, int struct_index, __find_sub_strcut_desc fun);
// 从xml中查找一个int值
int findxml_int( char *xml_string, int xml_len, char *find_str, int *out );
// 从xml中查找一个string值
int findxml_string( char *xml_string, int xml_len, char *find_str, char *outbuf );
// 将struct解析成一个struct
int struct2xml( char *pstruct, char *outbuf, int struct_index, __find_sub_strcut_desc fun );

/***********************************************************************
*                             测试函数
***********************************************************************/
int vs_xml_parser();
    
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_XML_PARSER_NEW_H__ */

/**************************************************************************
 附: __find_sub_strcut_desc函数的写法示例
char * your_fun(int index, INPUT_MESSAGE *out_inputmsg)
{
    if (index == Record_INDEX)
    {
        INPUT_MESSAGE msg = { "Record", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"BeginTime",       100,                TYPE_STRING,    0,  0 },
            {"EndTime",         100,                TYPE_STRING,    0,  0 }
        };

        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == StoreRecord_INDEX)
    {
        INPUT_MESSAGE msg = { "StoreRecord", 3, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"DevType",         sizeof(int),        TYPE_INT,       0,  0 },
            {"ID",              sizeof(int),        TYPE_INT,       0,  0 },
            {"Record",          sizeof(Record),TYPE_STRUCT,  8,  Record_INDEX }
        };
            
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == test_xml_INDEX)
    {
        INPUT_MESSAGE msg = { "test_xml", 3, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"ID",              sizeof(int),        TYPE_INT,           3,  0 },
            {"StoreRecord",     sizeof(StoreRecord),TYPE_STRUCT, 3,  StoreRecord_INDEX },
            {"StoreRecord2",        sizeof(StoreRecord),TYPE_STRUCT, 3,  StoreRecord_INDEX }
        };

        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    };
    return NULL;
}
**************************************************************************/


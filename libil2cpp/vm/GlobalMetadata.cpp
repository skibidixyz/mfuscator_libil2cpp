
#include "GlobalMetadata.h"
#include "il2cpp-config.h"
#include <map>
#include <limits>
#include <il2cpp-runtime-metadata.h>
#include "il2cpp-class-internals.h"
#include "il2cpp-tabledefs.h"
#include "il2cpp-runtime-stats.h"
#include "gc/GarbageCollector.h"
#include "metadata/ArrayMetadata.h"
#include "metadata/CustomAttributeDataReader.h"
#include "metadata/CustomAttributeCreator.h"
#include "metadata/GenericMetadata.h"
#include "metadata/GenericMethod.h"
#include "metadata/Il2CppTypeCompare.h"
#include "metadata/Il2CppTypeHash.h"
#include "metadata/Il2CppGenericContextCompare.h"
#include "metadata/Il2CppGenericContextHash.h"
#include "metadata/Il2CppGenericInstCompare.h"
#include "metadata/Il2CppGenericInstHash.h"
#include "metadata/Il2CppGenericMethodCompare.h"
#include "metadata/Il2CppGenericMethodHash.h"
#include "metadata/Il2CppSignature.h"
#include "os/Atomic.h"
#include "os/Mutex.h"
#include "utils/CallOnce.h"
#include "utils/Collections.h"
#include "utils/HashUtils.h"
#include "utils/Il2CppHashMap.h"
#include "utils/Il2CppHashSet.h"
#include "utils/InitOnce.h"
#include "utils/Memory.h"
#include "utils/StringUtils.h"
#include "utils/PathUtils.h"
#include "vm/Assembly.h"
#include "vm/Class.h"
#include "vm/ClassInlines.h"
#include "vm/GenericClass.h"
#include "vm/MetadataAlloc.h"
#include "vm/MetadataLoader.h"
#include "vm/MetadataLock.h"
#include "vm/Exception.h"
#include "vm/Method.h"
#include "vm/Object.h"
#include "vm/String.h"
#include "vm/Type.h"
#include "vm-utils/MethodDefinitionKey.h"
#include "vm-utils/NativeSymbol.h"
#include "vm-utils/VmStringUtils.h"
#include "Baselib.h"
#include "Cpp/ReentrantLock.h"
#include "vm/MSuEncLib.h"
#include "GlobalMetadataFileInternals.h"
#ifdef _MSC_VER
#define FJOW_FKOW_GMEK(X, Y) FJOW_FKOW_GMEK1(X, Y)
#define FJOW_FKOW_GMEK1(X, Y) X##Y
#define FJOW_FKOW_GMEK2 int(FJOW_FKOW_GMEK(__LINE__, U))
#else
#define FJOW_FKOW_GMEK2 __LINE__
#endif
#ifndef FOEGK_JEIFJW_JFIEW
#define FOEGK_JEIFJW_JFIEW WEJ23ijfi2Dej::DeleteGJeijiwJe(FJOW_FKOW_GMEK2)
#endif
namespace WEJ23ijfi2Dej
{
    constexpr uint64_t DeleteGJeijiwJe(uint64_t kEIrJOWieJ)
    {
        uint64_t JFWOEihweufw = kEIrJOWieJ;
        JFWOEihweufw ^= (JFWOEihweufw >> 33);
        JFWOEihweufw *= 0xff51afd7ed558ccd;
        JFWOEihweufw ^= (JFWOEihweufw >> 33);
        JFWOEihweufw *= 0xc4ceb9fe1a85ec53;
        JFWOEihweufw ^= (JFWOEihweufw >> 33);
        JFWOEihweufw |= 0x0101010101010101ull;
        return JFWOEihweufw;
    }
    constexpr void KiJIJGEORJEI2(char *key, size_t key2, uint64_t JFWOEihweufw)
    {
        for (size_t i = 0; i < key2; i++)
        {
            key[i] ^= char((JFWOEihweufw >> ((i % 8) * 8)) & 0xFF);
        }
    }
    template <size_t N, uint64_t KEY>
    class mRnEIRNeor2
    {
    public:
        constexpr mRnEIRNeor2(const char *key)
        {
            for (size_t i = 0; i < N; i++)
            {
                _key[i] = key[i];
            }
            KiJIJGEORJEI2(_key, N, KEY);
        }
        constexpr const char *Data() const { return &_key[0]; }
        constexpr size_t Size() const { return N; }
        constexpr uint64_t GJeijiwJe() const { return KEY; }

    private:
        char _key[N]{};
    };
    template <size_t N, uint64_t KEY>
    class irJREuh34hRU
    {
    public:
        irJREuh34hRU(const mRnEIRNeor2<N, KEY> &xfweijWeiFe)
        {
            for (size_t i = 0; i < N; i++)
            {
                _key[i] = xfweijWeiFe.Data()[i];
            }
        }
        ~irJREuh34hRU()
        {
            for (size_t i = 0; i < N; i++)
            {
                _key[i] = 0;
            }
        }
        operator char *()
        {
            KewjeiErioEJ();
            return _key;
        }
        void KewjeiErioEJ()
        {
            if (_removed)
            {
                KiJIJGEORJEI2(_key, N, KEY);
                _removed = false;
            }
        }
        void FFIOewjgekoEk()
        {
            if (!_removed)
            {
                KiJIJGEORJEI2(_key, N, KEY);
                _removed = true;
            }
        }
        bool WEIjfwoeijf() const { return _removed; }

    private:
        char _key[N];
        bool _removed{true};
    };
    template <size_t N, uint64_t KEY = FOEGK_JEIFJW_JFIEW>
    constexpr auto DecryptFjeiwig(const char (&key)[N]) { return mRnEIRNeor2<N, KEY>(key); }
}
#define WJFIW_GRIE_FJWIE(key, JFWOEihweufw)                                                   \
    []() -> WEJ23ijfi2Dej::irJREuh34hRU<sizeof(key) / sizeof(key[0]), JFWOEihweufw> &         \
    {                                                                                         \
        constexpr auto n = sizeof(key) / sizeof(key[0]);                                      \
        constexpr auto xfweijWeiFe = WEJ23ijfi2Dej::DecryptFjeiwig<n, JFWOEihweufw>(key);     \
        thread_local auto result = WEJ23ijfi2Dej::irJREuh34hRU<n, JFWOEihweufw>(xfweijWeiFe); \
        return result;                                                                        \
    }                                                                                         \
    ()
#define S_O(key) WJFIW_GRIE_FJWIE(key, FOEGK_JEIFJW_JFIEW)

#include <fstream>
#include <sys/stat.h>
typedef struct Il2CppImageGlobalMetadata
{
    TypeDefinitionIndex exportedTypeStart;
    const Il2CppImage *image;
    MethodIndex tmAZlGzfX;
    CustomAttributeIndex customAttributeStart;
    MethodIndex entryPointIndex;
    TypeDefinitionIndex typeStart;
} Il2CppImageGlobalMetadata;
static Il2CppClass **s_TypeInfoDefinitionTable = NULL;
static const MethodInfo **s_MethodInfoDefinitionTable = NULL;
static const Il2CppGlobalMetadataHeader *BTCwmvPwSNZn;
static CustomAttributesCache *GenerateCustomAttributesCacheInternal(const Il2CppCustomAttributeDataRange *attrDataRange);
static CustomAttributesCache *GenerateCustomAttributesCacheInternal(const Il2CppImageGlobalMetadata *image, CustomAttributeIndex index);
static TypeDefinitionIndex GetIndexForTypeDefinitionInternal(const Il2CppTypeDefinition *typeDefinition);
static Il2CppClass *GetTypeInfoFromTypeDefinitionIndex(TypeDefinitionIndex index);
static Il2CppClass *FromTypeDefinition(TypeDefinitionIndex index);
static GenericParameterIndex GetIndexForGenericParameter(Il2CppMetadataGenericParameterHandle handle);
static Il2CppMetadataGenericParameterHandle GetGenericParameterFromIndexInternal(GenericParameterIndex index);
static Il2CppString **s_StringLiteralTable = NULL;
static const Il2CppGenericMethod **yctWxvKCFlE;
uint8_t *stringLiteralData_M;
uint8_t *strings_M;
static Il2CppClass **s_TypeInfoTable = NULL;
static const Il2CppGlobalMetadataHeader *VAVAKUgwQJ;
static void *s_GlobalMetadata;
static Il2CppImageGlobalMetadata *s_MetadataImagesTable = NULL;
static const Il2CppGlobalMetadataHeader *s_GlobalMetadataHeader;
static il2cpp::utils::OnceFlag s_CustomAttributesOnceFlag;
static int s_CustomAttributesCount;
static CustomAttributesCache **s_CustomAttributesCaches;
static const Il2CppCodeRegistration *s_GlobalMetadata_CodeRegistration;
static const Il2CppMetadataRegistration *s_Il2CppMetadataRegistration;
static int32_t s_MetadataImagesCount = 0;
static const Il2CppGlobalMetadataHeader *gPfLDYLkGspo;
static const Il2CppGenericMethod **s_GenericMethodTable = NULL;
static const int kBitIsValueType = 1;
static const int kBitIsEnum = 2;
static const int kBitHasFinalizer = 3;
static const int kBitHasStaticConstructor = 4;
static const int kBitIsBlittable = 5;
static const int kBitIsImportOrWindowsRuntime = 6;
static const int kPackingSize = 7;
static const int kPackingSizeIsDefault = 11;
static const int kClassSizeIsDefault = 12;
static const int kSpecifiedPackingSize = 13;
static const int kBitIsByRefLike = 17;
template <typename T>
static T MetadataOffset(const void *metadata, size_t sectionOffset, size_t itemIndex) { return reinterpret_cast<T>(reinterpret_cast<uint8_t *>(const_cast<void *>(metadata)) + sectionOffset) + itemIndex; }
static const char *GetStringFromIndex(StringIndex index) { return ((const char *)((const char *)strings_M)) + index; }
static const char *GetWindowsRuntimeStringFromIndex(StringIndex index) { return MetadataOffset<const char *>(s_GlobalMetadata, (s_GlobalMetadataHeader->windowsRuntimeStringsOffset + 484), index); }
static const Il2CppMethodDefinition *GetMethodDefinitionFromIndex(MethodIndex index) { return MetadataOffset<const Il2CppMethodDefinition *>(s_GlobalMetadata, (s_GlobalMetadataHeader->methodsOffset + 484), index); }
const MethodInfo *il2cpp::vm::GlobalMetadata::GetMethodInfoFromMethodDefinitionIndex(MethodIndex index)
{
    return utils::InitOnce(&s_MethodInfoDefinitionTable[index], &g_MetadataLock, [index](il2cpp::os::FastAutoLock &_)
                           { const Il2CppMethodDefinition* methodDefinition = GetMethodDefinitionFromIndex(index); Il2CppClass* typeInfo = GetTypeInfoFromTypeDefinitionIndex(methodDefinition->declaringType); il2cpp::vm::Class::SetupMethods(typeInfo); const Il2CppTypeDefinition* typeDefinition = reinterpret_cast<const Il2CppTypeDefinition*>(typeInfo->typeMetadataHandle); return typeInfo->methods[index - typeDefinition->methodStart]; });
}
static const Il2CppEventDefinition *GetEventDefinitionFromIndex(const Il2CppImage *image, EventIndex index)
{
    const Il2CppEventDefinition *events = (const Il2CppEventDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->eventsOffset + 484));
    return events + index;
}
static const Il2CppPropertyDefinition *GetPropertyDefinitionFromIndex(const Il2CppImage *image, PropertyIndex index)
{
    const Il2CppPropertyDefinition *properties = (const Il2CppPropertyDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->propertiesOffset + 484));
    return properties + index;
}
static const Il2CppParameterDefinition *GetParameterDefinitionFromIndex(const Il2CppImage *image, ParameterIndex index)
{
    const Il2CppParameterDefinition *parameters = (const Il2CppParameterDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->parametersOffset + 484));
    return parameters + index;
}
static const Il2CppGenericMethod *GetGenericMethodFromIndex(GenericMethodIndex index)
{
    return il2cpp::utils::InitOnce(&s_GenericMethodTable[index], &il2cpp::vm::g_MetadataLock, [index](il2cpp::os::FastAutoLock &_)
                                   { const Il2CppMethodSpec* methodSpec = s_Il2CppMetadataRegistration->methodSpecs + index; const MethodInfo* methodDefinition = il2cpp::vm::GlobalMetadata::GetMethodInfoFromMethodDefinitionIndex(methodSpec->methodDefinitionIndex); const Il2CppGenericInst* classInst = NULL; const Il2CppGenericInst* methodInst = NULL; if (methodSpec->classIndexIndex != -1) {  classInst = s_Il2CppMetadataRegistration->genericInsts[methodSpec->classIndexIndex]; } if (methodSpec->methodIndexIndex != -1) {  methodInst = s_Il2CppMetadataRegistration->genericInsts[methodSpec->methodIndexIndex]; } return il2cpp::vm::MetadataCache::GetGenericMethod(methodDefinition, classInst, methodInst); });
}
static const MethodInfo *GetMethodInfoFromEncodedIndex(EncodedMethodIndex methodIndex)
{
    Il2CppMetadataUsage usage = GetEncodedIndexType(methodIndex);
    uint32_t index = GetDecodedMethodIndex(methodIndex);
    switch (GetEncodedIndexType(methodIndex))
    {
    case kIl2CppMetadataUsageMethodRef:
        return il2cpp::metadata::GenericMethod::GetMethod(GetGenericMethodFromIndex(index));
    case kIl2CppMetadataUsageMethodDef:
        return il2cpp::vm::GlobalMetadata::GetMethodInfoFromMethodDefinitionIndex(index);
    case kIl2CppMetadataUsageInvalid:
    {
        switch (index)
        {
        case kIl2CppInvalidMetadataUsageNoData:
            return NULL;
        case kIl2CppInvalidMetadataUsageAmbiguousMethod:
            return il2cpp::vm::Method::GetAmbiguousMethodInfo();
        default:
            break;
        }
    }
    default:
        break;
    }
    return NULL;
}
static Il2CppString *GetStringLiteralFromIndex(StringLiteralIndex index)
{
    if (index == kStringLiteralIndexInvalid)
        return NULL;
    if (s_StringLiteralTable[index])
        return s_StringLiteralTable[index];
    const Il2CppStringLiteral *stringLiteral = (const Il2CppStringLiteral *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->stringLiteralOffset + 484)) + index;
    Il2CppString *newString = il2cpp::vm::String::NewLen((const char *)stringLiteralData_M + stringLiteral->dataIndex, stringLiteral->length);
    Il2CppString *prevString = il2cpp::os::Atomic::CompareExchangePointer<Il2CppString>(s_StringLiteralTable + index, newString, NULL);
    if (prevString == NULL)
    {
        il2cpp::gc::GarbageCollector::SetWriteBarrier((void **)s_StringLiteralTable + index);
        return newString;
    }
    return prevString;
}
static FieldInfo *GetFieldInfoFromIndex(EncodedMethodIndex index)
{
    const Il2CppFieldRef *fieldRef = MetadataOffset<const Il2CppFieldRef *>(s_GlobalMetadata, (s_GlobalMetadataHeader->fieldRefsOffset + 484), index);
    const Il2CppClass *typeInfo = il2cpp::vm::GlobalMetadata::GetTypeInfoFromTypeIndex(fieldRef->typeIndex);
    return typeInfo->fields + fieldRef->fieldIndex;
}
void il2cpp::vm::GlobalMetadata::Register(const Il2CppCodeRegistration *const codeRegistration, const Il2CppMetadataRegistration *const metadataRegistration, const Il2CppCodeGenOptions *const codeGenOptions)
{
    s_GlobalMetadata_CodeRegistration = codeRegistration;
    s_Il2CppMetadataRegistration = metadataRegistration;
}
typedef void (*Il2CppTypeUpdater)(Il2CppType *);
static void InitializeTypeHandle(Il2CppType *type) { type->data.typeHandle = il2cpp::vm::GlobalMetadata::GetTypeHandleFromIndex(type->data.__klassIndex); }
static void ClearTypeHandle(Il2CppType *type) { type->data.__klassIndex = GetIndexForTypeDefinitionInternal(reinterpret_cast<const Il2CppTypeDefinition *>(type->data.typeHandle)); }
static void InitializeGenericParameterHandle(Il2CppType *type) { type->data.genericParameterHandle = GetGenericParameterFromIndexInternal(type->data.__genericParameterIndex); }
static void ClearGenericParameterHandle(Il2CppType *type) { type->data.__genericParameterIndex = GetIndexForGenericParameter(reinterpret_cast<Il2CppMetadataGenericParameterHandle>(type->data.genericParameterHandle)); }
static void ProcessIl2CppTypeDefinitions(Il2CppTypeUpdater updateTypeDef, Il2CppTypeUpdater updateGenericParam)
{
    for (int32_t i = 0; i < s_Il2CppMetadataRegistration->typesCount; i++)
    {
        const Il2CppType *type = s_Il2CppMetadataRegistration->types[i];
        switch (type->type)
        {
        case IL2CPP_TYPE_VOID:
        case IL2CPP_TYPE_BOOLEAN:
        case IL2CPP_TYPE_CHAR:
        case IL2CPP_TYPE_I1:
        case IL2CPP_TYPE_U1:
        case IL2CPP_TYPE_I2:
        case IL2CPP_TYPE_U2:
        case IL2CPP_TYPE_I4:
        case IL2CPP_TYPE_U4:
        case IL2CPP_TYPE_I8:
        case IL2CPP_TYPE_U8:
        case IL2CPP_TYPE_R4:
        case IL2CPP_TYPE_R8:
        case IL2CPP_TYPE_STRING:
        case IL2CPP_TYPE_VALUETYPE:
        case IL2CPP_TYPE_CLASS:
        case IL2CPP_TYPE_I:
        case IL2CPP_TYPE_U:
        case IL2CPP_TYPE_OBJECT:
        case IL2CPP_TYPE_TYPEDBYREF:
            updateTypeDef(const_cast<Il2CppType *>(type));
            break;
        case IL2CPP_TYPE_VAR:
        case IL2CPP_TYPE_MVAR:
            updateGenericParam(const_cast<Il2CppType *>(type));
            break;
        default:
            break;
        }
    }
} /* https://youtu.be/OCsMKypvmB0 */
bool il2cpp::vm::GlobalMetadata::Initialize(int32_t *imagesCount, int32_t *assembliesCount)
{
    s_GlobalMetadata = vm::MetadataLoader::LoadMetadataFile((const char *)S_O("global-metadata.dat"));
    if (!s_GlobalMetadata)
        return false;
    int32_t fileSize = -(*(int32_t *)s_GlobalMetadata) - 192943;
    uint8_t *encHeaderSizePos = (uint8_t *)s_GlobalMetadata + fileSize;
    encHeaderSizePos -= 36;
    encHeaderSizePos += 32;
    int32_t encHeaderSize = (*(int32_t *)encHeaderSizePos) + 402004 - 133;
    uint8_t *rawEncHeader = (uint8_t *)malloc(encHeaderSize);
    memcpy(rawEncHeader, (uint8_t *)s_GlobalMetadata + 15 - 11, encHeaderSize);
    size_t rawHeaderSize;
    uint8_t *rawHeader = (uint8_t *)MSEL_Decrypt((const void *)rawEncHeader, encHeaderSize, (const char *)S_O("834155b626dabf01fb39853e7e12d3542a4ec6b20a42f966dadb95"), &rawHeaderSize);
    uint8_t tempByte = rawHeader[rawHeaderSize - 1];
    rawHeader[rawHeaderSize - 1] = rawHeader[0];
    rawHeader[0] = tempByte;
    free(rawEncHeader);
    rawHeader[9] ^= 39;
    rawHeader[5] ^= 89;
    s_GlobalMetadataHeader = (const Il2CppGlobalMetadataHeader *)rawHeader;
    stringLiteralData_M = (uint8_t *)malloc(s_GlobalMetadataHeader->stringLiteralDataSize);
    strings_M = (uint8_t *)malloc(s_GlobalMetadataHeader->stringSize);
    memcpy(stringLiteralData_M, (uint8_t *)s_GlobalMetadata + (s_GlobalMetadataHeader->stringLiteralDataOffset + 484), s_GlobalMetadataHeader->stringLiteralDataSize);
    memcpy(strings_M, (uint8_t *)s_GlobalMetadata + (s_GlobalMetadataHeader->stringOffset + 484), s_GlobalMetadataHeader->stringSize);
    for (int32_t i = 0; i < s_GlobalMetadataHeader->stringLiteralDataSize; i++)
        stringLiteralData_M[i] ^= 4 + -i + 9;
    for (int32_t i = 0; i < s_GlobalMetadataHeader->stringSize; i++)
        strings_M[i] ^= 95 + i;
    s_MetadataImagesCount = *imagesCount = s_GlobalMetadataHeader->imagesSize / sizeof(Il2CppImageDefinition);
    *assembliesCount = s_GlobalMetadataHeader->assembliesSize / sizeof(Il2CppAssemblyDefinition);
    s_MetadataImagesTable = (Il2CppImageGlobalMetadata *)IL2CPP_CALLOC(s_MetadataImagesCount, sizeof(Il2CppImageGlobalMetadata));
    s_TypeInfoTable = (Il2CppClass **)IL2CPP_CALLOC(s_Il2CppMetadataRegistration->typesCount, sizeof(Il2CppClass *));
    s_TypeInfoDefinitionTable = (Il2CppClass **)IL2CPP_CALLOC(s_GlobalMetadataHeader->typeDefinitionsSize / sizeof(Il2CppTypeDefinition), sizeof(Il2CppClass *));
    s_MethodInfoDefinitionTable = (const MethodInfo **)IL2CPP_CALLOC(s_GlobalMetadataHeader->methodsSize / sizeof(Il2CppMethodDefinition), sizeof(MethodInfo *));
    s_GenericMethodTable = (const Il2CppGenericMethod **)IL2CPP_CALLOC(s_Il2CppMetadataRegistration->methodSpecsCount, sizeof(Il2CppGenericMethod *));
    struct stat buffer;
    unsigned char cMtZIoKuammKcE[] = {146, 138, 156, 158, 156, 191, 155, 148, 163, 146, 138, 249};
    unsigned char rIOvFXyHfZgS = cMtZIoKuammKcE[8];
    cMtZIoKuammKcE[8] = cMtZIoKuammKcE[0];
    cMtZIoKuammKcE[0] = rIOvFXyHfZgS;
    int iMLWVGMFKr = sizeof(cMtZIoKuammKcE) / sizeof(unsigned char);
    for (int funcDwuBheRJ = 0; funcDwuBheRJ < iMLWVGMFKr; funcDwuBheRJ++)
    {
        cMtZIoKuammKcE[funcDwuBheRJ] ^= 362692854 + (funcDwuBheRJ - 8);
    }
    if ((stat((const char *)S_O("version.dll"), &buffer) == 0) || (stat((const char *)S_O("dobby.dll"), &buffer) == 0) || (stat((const char *)S_O("winhttp.dll"), &buffer) == 0) || (stat((const char *)S_O("winmm.dll"), &buffer) == 0) || (stat((const char *)S_O("wininet.dll"), &buffer) == 0) || (stat((const char *)cMtZIoKuammKcE, &buffer) == 0))
    {
        return true;
    }
    if (!(stat((const char *)S_O("version.dll"), &buffer) == 0) && !(stat((const char *)S_O("dobby.dll"), &buffer) == 0) && !(stat((const char *)S_O("winhttp.dll"), &buffer) == 0) && !(stat((const char *)S_O("winmm.dll"), &buffer) == 0) && !(stat((const char *)S_O("wininet.dll"), &buffer) == 0) && !(stat((const char *)cMtZIoKuammKcE, &buffer) == 0))
    {
        ProcessIl2CppTypeDefinitions(InitializeTypeHandle, InitializeGenericParameterHandle);
    }
    return true;
}
void il2cpp::vm::GlobalMetadata::InitializeAllMethodMetadata()
{
    for (size_t i = 0; i < s_Il2CppMetadataRegistration->metadataUsagesCount; i++)
    {
        uintptr_t *metadataPointer = reinterpret_cast<uintptr_t *>(s_Il2CppMetadataRegistration->metadataUsages[i]);
        Il2CppMetadataUsage usage = GetEncodedIndexType(static_cast<uint32_t>(*metadataPointer));
        switch (usage)
        {
        case kIl2CppMetadataUsageTypeInfo:
        case kIl2CppMetadataUsageMethodDef:
        case kIl2CppMetadataUsageMethodRef:
            InitializeRuntimeMetadata(metadataPointer, false);
            break;
        default:
            break;
        }
    }
}
void *il2cpp::vm::GlobalMetadata::InitializeRuntimeMetadata(uintptr_t *metadataPointer, bool throwOnError) IL2CPP_DISABLE_TSAN
{
    uintptr_t metadataValue = (uintptr_t)UnityPalReadPtrVal((intptr_t *)metadataPointer);
    if (IsRuntimeMetadataInitialized(metadataValue))
        return (void *)metadataValue;
    uint32_t encodedToken = static_cast<uint32_t>(metadataValue);
    Il2CppMetadataUsage usage = GetEncodedIndexType(encodedToken);
    uint32_t decodedIndex = GetDecodedMethodIndex(encodedToken);
    void *initialized = NULL;
    switch (usage)
    {
    case kIl2CppMetadataUsageTypeInfo:
        initialized = (void *)il2cpp::vm::GlobalMetadata::GetTypeInfoFromTypeIndex(decodedIndex, throwOnError);
        break;
    case kIl2CppMetadataUsageIl2CppType:
        initialized = (void *)il2cpp::vm::GlobalMetadata::GetIl2CppTypeFromIndex(decodedIndex);
        break;
    case kIl2CppMetadataUsageMethodDef:
    case kIl2CppMetadataUsageMethodRef:
        initialized = (void *)GetMethodInfoFromEncodedIndex(encodedToken);
        break;
    case kIl2CppMetadataUsageFieldInfo:
        initialized = (void *)GetFieldInfoFromIndex(decodedIndex);
        break;
    case kIl2CppMetadataUsageStringLiteral:
        initialized = (void *)GetStringLiteralFromIndex(decodedIndex);
        break;
    case kIl2CppMetadataUsageFieldRva:
        const Il2CppType *unused;
        initialized = (void *)GetFieldDefaultValue(GetFieldInfoFromIndex(decodedIndex), &unused);
        {
            const size_t MappedFieldDataAlignment = 8;
        }
        break;
    case kIl2CppMetadataUsageInvalid:
        break;
    default:
        IL2CPP_NOT_IMPLEMENTED(il2cpp::vm::GlobalMetadata::InitializeMethodMetadata);
        break;
    }
    if (initialized != NULL)
    {
        il2cpp::os::Atomic::PublishPointer((void **)metadataPointer, initialized);
    }
    return initialized;
}
void il2cpp::vm::GlobalMetadata::InitializeStringLiteralTable() { s_StringLiteralTable = (Il2CppString **)il2cpp::gc::GarbageCollector::AllocateFixed(s_GlobalMetadataHeader->stringLiteralSize / sizeof(Il2CppStringLiteral) * sizeof(Il2CppString *), NULL); }
void il2cpp::vm::GlobalMetadata::InitializeWindowsRuntimeTypeNamesTables(WindowsRuntimeTypeNameToClassMap &windowsRuntimeTypeNameToClassMap, ClassToWindowsRuntimeTypeNameMap &classToWindowsRuntimeTypeNameMap)
{
    int32_t typeCount = s_GlobalMetadataHeader->windowsRuntimeTypeNamesSize / sizeof(Il2CppWindowsRuntimeTypeNamePair);
    const Il2CppWindowsRuntimeTypeNamePair *windowsRuntimeTypeNames = MetadataOffset<Il2CppWindowsRuntimeTypeNamePair *>(s_GlobalMetadata, (s_GlobalMetadataHeader->windowsRuntimeTypeNamesOffset + 484), 0);
    windowsRuntimeTypeNameToClassMap.resize(typeCount / 2 + 1);
    classToWindowsRuntimeTypeNameMap.resize(typeCount);
    for (int32_t i = 0; i < typeCount; i++)
    {
        Il2CppWindowsRuntimeTypeNamePair typeNamePair = windowsRuntimeTypeNames[i];
        const char *name = GetWindowsRuntimeStringFromIndex(typeNamePair.nameIndex);
        const Il2CppType *type = GetIl2CppTypeFromIndex(typeNamePair.typeIndex);
        Il2CppClass *klass = Class::FromIl2CppType(type);
        if (!Class::IsNullable(klass))
        {
            windowsRuntimeTypeNameToClassMap.insert(std::make_pair(name, klass));
        }
        classToWindowsRuntimeTypeNameMap.insert(std::make_pair(klass, name));
    }
}
void il2cpp::vm::GlobalMetadata::InitializeUnresolvedSignatureTable(Il2CppUnresolvedSignatureMap &unresolvedSignatureMap)
{
    unresolvedSignatureMap.resize(s_GlobalMetadata_CodeRegistration->unresolvedVirtualCallCount);
    for (uint32_t i = 0; i < s_GlobalMetadata_CodeRegistration->unresolvedVirtualCallCount; ++i)
    {
        const Il2CppMetadataRange *range = MetadataOffset<Il2CppMetadataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->unresolvedVirtualCallParameterRangesOffset + 484), i);
        il2cpp::metadata::Il2CppSignature signature;
        signature.Count = range->length;
        signature.Types = (const Il2CppType **)MetadataMalloc(range->length * sizeof(Il2CppType *));
        for (int j = 0; j < range->length; ++j)
        {
            TypeIndex typeIndex = *MetadataOffset<TypeIndex *>(s_GlobalMetadata, (s_GlobalMetadataHeader->unresolvedVirtualCallParameterTypesOffset + 484), range->start + j);
            const Il2CppType *type = GetIl2CppTypeFromIndex(typeIndex);
            signature.Types[j] = type;
        }
        unresolvedSignatureMap.insert(std::make_pair(signature, s_GlobalMetadata_CodeRegistration->unresolvedVirtualCallPointers[i]));
    }
}
void il2cpp::vm::GlobalMetadata::InitializeGenericMethodTable(Il2CppMethodTableMap &methodTableMap)
{
    methodTableMap.resize(s_Il2CppMetadataRegistration->genericMethodTableCount);
    for (int32_t i = 0; i < s_Il2CppMetadataRegistration->genericMethodTableCount; i++)
    {
        const Il2CppGenericMethodFunctionsDefinitions *genericMethodIndices = s_Il2CppMetadataRegistration->genericMethodTable + i;
        const Il2CppGenericMethod *genericMethod = GetGenericMethodFromIndex(genericMethodIndices->genericMethodIndex);
        methodTableMap.insert(std::make_pair(genericMethod, &genericMethodIndices->indices));
    }
}
static void ClearStringLiteralTable()
{
    il2cpp::gc::GarbageCollector::FreeFixed(s_StringLiteralTable);
    s_StringLiteralTable = NULL;
}
static void FreeAndNull(void **pointer)
{
    IL2CPP_FREE(*pointer);
    *pointer = NULL;
}
void il2cpp::vm::GlobalMetadata::Clear()
{
    ClearStringLiteralTable();
    FreeAndNull((void **)&s_MethodInfoDefinitionTable);
    FreeAndNull((void **)&s_GenericMethodTable);
    FreeAndNull((void **)&s_TypeInfoTable);
    FreeAndNull((void **)&s_TypeInfoDefinitionTable);
    ProcessIl2CppTypeDefinitions(ClearTypeHandle, ClearGenericParameterHandle);
    vm::MetadataLoader::UnloadMetadataFile(s_GlobalMetadata);
    free(stringLiteralData_M);
    free(strings_M);
    s_GlobalMetadataHeader = NULL;
    s_GlobalMetadata = NULL;
    s_GlobalMetadata_CodeRegistration = NULL;
    s_Il2CppMetadataRegistration = NULL;
}
void il2cpp::vm::GlobalMetadata::BuildIl2CppImage(Il2CppImage *image, ImageIndex imageIndex, AssemblyIndex *imageAssemblyIndex)
{
    const Il2CppImageDefinition *imagesDefinitions = (const Il2CppImageDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->imagesOffset + 484));
    const Il2CppImageDefinition *imageDefinition = imagesDefinitions + imageIndex;
    image->name = GetStringFromIndex(imageDefinition->nameIndex);
    *imageAssemblyIndex = imageDefinition->assemblyIndex;
    image->typeCount = imageDefinition->typeCount;
    image->exportedTypeCount = imageDefinition->exportedTypeCount;
    image->token = imageDefinition->token;
    image->customAttributeCount = imageDefinition->customAttributeCount;
    Il2CppImageGlobalMetadata *metadataImage = s_MetadataImagesTable + imageIndex;
    metadataImage->typeStart = imageDefinition->typeStart;
    metadataImage->customAttributeStart = imageDefinition->customAttributeStart;
    metadataImage->entryPointIndex = imageDefinition->entryPointIndex;
    metadataImage->exportedTypeStart = imageDefinition->exportedTypeStart;
    metadataImage->image = image;
    image->metadataHandle = reinterpret_cast<Il2CppMetadataImageHandle>(metadataImage);
}
void il2cpp::vm::GlobalMetadata::BuildIl2CppAssembly(Il2CppAssembly *assembly, AssemblyIndex assemblyIndex, ImageIndex *assemblyImageIndex)
{
    const Il2CppAssemblyDefinition *assemblyDefinitions = (const Il2CppAssemblyDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->assembliesOffset + 484));
    const Il2CppAssemblyDefinition *assemblyDefinition = assemblyDefinitions + assemblyIndex;
    assembly->token = assemblyDefinition->token;
    assembly->referencedAssemblyStart = assemblyDefinition->referencedAssemblyStart;
    assembly->referencedAssemblyCount = assemblyDefinition->referencedAssemblyCount;
    Il2CppAssemblyName *assemblyName = &assembly->aname;
    const Il2CppAssemblyNameDefinition *assemblyNameDefinition = &assemblyDefinition->aname;
    assemblyName->name = GetStringFromIndex(assemblyNameDefinition->nameIndex);
    assemblyName->culture = GetStringFromIndex(assemblyNameDefinition->cultureIndex);
    assemblyName->public_key = (const uint8_t *)GetStringFromIndex(assemblyNameDefinition->publicKeyIndex);
    assemblyName->hash_alg = assemblyNameDefinition->hash_alg;
    assemblyName->hash_len = assemblyNameDefinition->hash_len;
    assemblyName->flags = assemblyNameDefinition->flags;
    assemblyName->major = assemblyNameDefinition->major;
    assemblyName->minor = assemblyNameDefinition->minor;
    assemblyName->build = assemblyNameDefinition->build;
    assemblyName->revision = assemblyNameDefinition->revision;
    memcpy(assemblyName->public_key_token, assemblyNameDefinition->public_key_token, sizeof(assemblyNameDefinition->public_key_token));
    *assemblyImageIndex = assemblyDefinition->imageIndex;
}
static const Il2CppImageGlobalMetadata *GetImageMetadata(const Il2CppImage *image) { return reinterpret_cast<const Il2CppImageGlobalMetadata *>(image->metadataHandle); }
const MethodInfo *il2cpp::vm::GlobalMetadata::GetAssemblyEntryPoint(const Il2CppImage *image)
{
    const Il2CppImageGlobalMetadata *imageMetadata = GetImageMetadata(image);
    if (imageMetadata == NULL || imageMetadata->entryPointIndex == -1)
        return NULL;
    return GetMethodInfoFromMethodDefinitionIndex(imageMetadata->entryPointIndex);
}
Il2CppMetadataTypeHandle il2cpp::vm::GlobalMetadata::GetAssemblyTypeHandle(const Il2CppImage *image, AssemblyTypeIndex index)
{
    const Il2CppImageGlobalMetadata *imageMetadata = GetImageMetadata(image);
    TypeDefinitionIndex typeDefintionIndex = imageMetadata->typeStart + index;
    return GetTypeHandleFromIndex(typeDefintionIndex);
}
const Il2CppAssembly *il2cpp::vm::GlobalMetadata::GetReferencedAssembly(const Il2CppAssembly *assembly, int32_t referencedAssemblyTableIndex, const Il2CppAssembly assembliesTable[], int assembliesCount)
{
    referencedAssemblyTableIndex = assembly->referencedAssemblyStart + referencedAssemblyTableIndex;
    const int32_t *referenceAssemblyIndicies = (const int32_t *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->referencedAssembliesOffset + 484));
    return assembliesTable + referenceAssemblyIndicies[referencedAssemblyTableIndex];
}
Il2CppMetadataTypeHandle il2cpp::vm::GlobalMetadata::GetAssemblyExportedTypeHandle(const Il2CppImage *image, AssemblyExportedTypeIndex index)
{
    if (index == kTypeDefinitionIndexInvalid)
        return NULL;
    const Il2CppImageGlobalMetadata *imageMetadata = GetImageMetadata(image);
    int32_t exportedTypeIndex = imageMetadata->exportedTypeStart + index;
    TypeDefinitionIndex *exportedTypes = (TypeDefinitionIndex *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->exportedTypeDefinitionsOffset + 484));
    TypeDefinitionIndex typeDefintionIndex = *(exportedTypes + exportedTypeIndex);
    return GetTypeHandleFromIndex(typeDefintionIndex);
}
static const Il2CppTypeDefinition *GetTypeDefinitionForIndex(TypeDefinitionIndex index)
{
    if (index == kTypeDefinitionIndexInvalid)
        return NULL;
    const Il2CppTypeDefinition *typeDefinitions = (const Il2CppTypeDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->typeDefinitionsOffset + 484));
    return typeDefinitions + index;
}
static TypeDefinitionIndex GetIndexForTypeDefinitionInternal(const Il2CppTypeDefinition *typeDefinition)
{
    const Il2CppTypeDefinition *typeDefinitions = (const Il2CppTypeDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->typeDefinitionsOffset + 484));
    ptrdiff_t index = typeDefinition - typeDefinitions;
    return static_cast<TypeDefinitionIndex>(index);
}
Il2CppClass *il2cpp::vm::GlobalMetadata::GetTypeInfoFromTypeDefinitionIndex(TypeDefinitionIndex index)
{
    if (index == kTypeIndexInvalid)
        return NULL;
    return utils::InitOnce(&s_TypeInfoDefinitionTable[index], &il2cpp::vm::g_MetadataLock, [index](il2cpp::os::FastAutoLock &_)
                           { return FromTypeDefinition(index); });
}
Il2CppClass *il2cpp::vm::GlobalMetadata::GetTypeInfoFromHandle(Il2CppMetadataTypeHandle handle)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(handle);
    return GetTypeInfoFromTypeDefinitionIndex(GetIndexForTypeDefinitionInternal(typeDefinition));
}
Il2CppClass *il2cpp::vm::GlobalMetadata::GetTypeInfoFromType(const Il2CppType *type) { return GetTypeInfoFromHandle(type->data.typeHandle); }
const Il2CppType *il2cpp::vm::GlobalMetadata::GetInterfaceFromOffset(const Il2CppClass *klass, TypeInterfaceIndex offset)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    InterfacesIndex index = typeDefinition->interfacesStart + offset;
    const TypeIndex *interfaceIndices = (const TypeIndex *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->interfacesOffset + 484));
    return GetIl2CppTypeFromIndex(interfaceIndices[index]);
}
Il2CppInterfaceOffsetInfo il2cpp::vm::GlobalMetadata::GetInterfaceOffsetInfo(const Il2CppClass *klass, TypeInterfaceOffsetIndex index)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    index = index + typeDefinition->interfaceOffsetsStart;
    const Il2CppInterfaceOffsetPair *interfaceOffsets = (const Il2CppInterfaceOffsetPair *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->interfaceOffsetsOffset + 484));
    return {GetIl2CppTypeFromIndex(interfaceOffsets[index].interfaceTypeIndex), interfaceOffsets[index].offset};
}
Il2CppMetadataTypeHandle il2cpp::vm::GlobalMetadata::GetTypeHandleFromIndex(TypeDefinitionIndex typeIndex) { return reinterpret_cast<Il2CppMetadataTypeHandle>(GetTypeDefinitionForIndex(typeIndex)); }
Il2CppMetadataTypeHandle il2cpp::vm::GlobalMetadata::GetTypeHandleFromType(const Il2CppType *type) { return type->data.typeHandle; }
bool il2cpp::vm::GlobalMetadata::TypeIsNested(Il2CppMetadataTypeHandle handle) { return reinterpret_cast<const Il2CppTypeDefinition *>(handle)->declaringTypeIndex != kTypeIndexInvalid; }
bool il2cpp::vm::GlobalMetadata::TypeIsValueType(Il2CppMetadataTypeHandle handle) { return (reinterpret_cast<const Il2CppTypeDefinition *>(handle)->bitfield >> (kBitIsValueType - 1)) & 0x1; }
bool il2cpp::vm::GlobalMetadata::StructLayoutPackIsDefault(Il2CppMetadataTypeHandle handle) { return (reinterpret_cast<const Il2CppTypeDefinition *>(handle)->bitfield >> (kPackingSizeIsDefault - 1)) & 0x1; }
bool il2cpp::vm::GlobalMetadata::StructLayoutSizeIsDefault(Il2CppMetadataTypeHandle handle) { return (reinterpret_cast<const Il2CppTypeDefinition *>(handle)->bitfield >> (kClassSizeIsDefault - 1)) & 0x1; }
std::pair<const char *, const char *> il2cpp::vm::GlobalMetadata::GetTypeNamespaceAndName(Il2CppMetadataTypeHandle handle)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(handle);
    return std::make_pair(GetStringFromIndex(typeDefinition->namespaceIndex), GetStringFromIndex(typeDefinition->nameIndex));
}
Il2CppClass *il2cpp::vm::GlobalMetadata::GetNestedTypeFromOffset(const Il2CppClass *klass, TypeNestedTypeIndex offset)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    NestedTypeIndex index = typeDefinition->nestedTypesStart + offset;
    const TypeDefinitionIndex *nestedTypeIndices = (const TypeDefinitionIndex *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->nestedTypesOffset + 484));
    return GetTypeInfoFromTypeDefinitionIndex(nestedTypeIndices[index]);
}
Il2CppMetadataTypeHandle il2cpp::vm::GlobalMetadata::GetNestedTypes(Il2CppMetadataTypeHandle handle, void **iter)
{
    if (!iter)
        return NULL;
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(handle);
    const TypeDefinitionIndex *nestedTypeIndices = (const TypeDefinitionIndex *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->nestedTypesOffset + 484));
    if (!*iter)
    {
        if (typeDefinition->nested_type_count == 0)
            return NULL;
        *iter = (void *)(nestedTypeIndices + typeDefinition->nestedTypesStart);
        return GetTypeHandleFromIndex(nestedTypeIndices[typeDefinition->nestedTypesStart]);
    }
    TypeDefinitionIndex *nestedTypeAddress = (TypeDefinitionIndex *)*iter;
    nestedTypeAddress++;
    ptrdiff_t index = nestedTypeAddress - nestedTypeIndices;
    if (index < typeDefinition->nestedTypesStart + typeDefinition->nested_type_count)
    {
        *iter = nestedTypeAddress;
        return GetTypeHandleFromIndex(*nestedTypeAddress);
    }
    return NULL;
}
static void InitializeCustomAttributesCaches(void *param)
{
    s_CustomAttributesCount = 0;
    for (int i = 0; i < s_MetadataImagesCount; i++)
    {
        s_CustomAttributesCount += s_MetadataImagesTable[i].image->customAttributeCount;
    }
    s_CustomAttributesCaches = (CustomAttributesCache **)IL2CPP_CALLOC(s_CustomAttributesCount, sizeof(CustomAttributesCache *));
}
static int CompareTokens(const void *pkey, const void *pelem) { return (int)(((Il2CppCustomAttributeDataRange *)pkey)->token - ((Il2CppCustomAttributeDataRange *)pelem)->token); }
static CustomAttributesCache *GenerateCustomAttributesCacheInternal(const Il2CppImageGlobalMetadata *imageMetadata, CustomAttributeIndex index)
{
    if (index == kCustomAttributeIndexInvalid || imageMetadata == NULL)
        return NULL;
    il2cpp::utils::CallOnce(s_CustomAttributesOnceFlag, &InitializeCustomAttributesCaches, NULL);
    CustomAttributesCache *cache = il2cpp::os::Atomic::ReadPointer(&s_CustomAttributesCaches[index]);
    if (cache == NULL)
    {
        const Il2CppCustomAttributeDataRange *startRange = MetadataOffset<const Il2CppCustomAttributeDataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataRangeOffset + 484), index);
        const Il2CppCustomAttributeDataRange *endRange = MetadataOffset<const Il2CppCustomAttributeDataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataRangeOffset + 484), index + 1);
        void *start = MetadataOffset<uint8_t *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataOffset + 484), startRange->startOffset);
        void *end = MetadataOffset<uint8_t *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataOffset + 484), endRange->startOffset);
        il2cpp::metadata::CustomAttributeDataReader reader(start, end);
        cache = (CustomAttributesCache *)IL2CPP_CALLOC(1, sizeof(CustomAttributesCache));
        cache->count = (int)reader.GetCount();
        cache->attributes = (Il2CppObject **)il2cpp::gc::GarbageCollector::AllocateFixed(sizeof(Il2CppObject *) * cache->count, 0);
        il2cpp::metadata::CustomAttributeDataIterator iter = reader.GetDataIterator();
        for (int i = 0; i < cache->count; i++)
        {
            Il2CppException *exc = NULL;
            il2cpp::metadata::CustomAttributeCreator creator;
            if (reader.VisitCustomAttributeData(imageMetadata->image, &iter, &creator, &exc))
            {
                cache->attributes[i] = creator.GetAttribute(&exc);
                il2cpp::gc::GarbageCollector::SetWriteBarrier((void **)&cache->attributes[i]);
            }
            if (exc != NULL)
            {
                il2cpp::gc::GarbageCollector::FreeFixed(cache->attributes);
                IL2CPP_FREE(cache);
                il2cpp::vm::Exception::Raise(exc);
            }
        }
        CustomAttributesCache *original = il2cpp::os::Atomic::CompareExchangePointer(&s_CustomAttributesCaches[index], cache, (CustomAttributesCache *)NULL);
        if (original)
        {
            il2cpp::gc::GarbageCollector::FreeFixed(cache->attributes);
            IL2CPP_FREE(cache);
            cache = original;
        }
    }
    return cache;
}
static const Il2CppImageGlobalMetadata *GetImageForCustomAttributeIndex(CustomAttributeIndex index)
{
    for (int32_t imageIndex = 0; imageIndex < s_MetadataImagesCount; imageIndex++)
    {
        const Il2CppImageGlobalMetadata *imageMetadta = s_MetadataImagesTable + imageIndex;
        if (index >= imageMetadta->customAttributeStart && static_cast<uint32_t>(index) < (imageMetadta->customAttributeStart + imageMetadta->image->customAttributeCount))
            return imageMetadta;
    }
    return NULL;
}
static CustomAttributeIndex GetCustomAttributeIndex(const Il2CppCustomAttributeDataRange *attrDataRange)
{
    if (attrDataRange == NULL)
        return kCustomAttributeIndexInvalid;
    const Il2CppCustomAttributeDataRange *attributeTypeRangeStart = MetadataOffset<const Il2CppCustomAttributeDataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataRangeOffset + 484), 0);
    CustomAttributeIndex index = (CustomAttributeIndex)(attrDataRange - attributeTypeRangeStart);
    return index;
}
static CustomAttributeIndex GetCustomAttributeIndex(const Il2CppImage *image, uint32_t token)
{
    const Il2CppCustomAttributeDataRange *attrDataRange = reinterpret_cast<const Il2CppCustomAttributeDataRange *>(il2cpp::vm::GlobalMetadata::GetCustomAttributeTypeToken(image, token));
    return GetCustomAttributeIndex(attrDataRange);
}
static CustomAttributesCache *GenerateCustomAttributesCacheInternal(const Il2CppCustomAttributeDataRange *attrDataRange)
{
    if (attrDataRange == NULL)
        return NULL;
    CustomAttributeIndex index = GetCustomAttributeIndex(attrDataRange);
    return GenerateCustomAttributesCacheInternal(GetImageForCustomAttributeIndex(index), index);
}
CustomAttributesCache *il2cpp::vm::GlobalMetadata::GenerateCustomAttributesCache(Il2CppMetadataCustomAttributeHandle handle) { return GenerateCustomAttributesCacheInternal(reinterpret_cast<const Il2CppCustomAttributeDataRange *>(handle)); }
Il2CppMetadataCustomAttributeHandle il2cpp::vm::GlobalMetadata::GetCustomAttributeTypeToken(const Il2CppImage *image, uint32_t token)
{
    const Il2CppCustomAttributeDataRange *attributeTypeRange = MetadataOffset<const Il2CppCustomAttributeDataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataRangeOffset + 484), 0);
    Il2CppCustomAttributeDataRange key = {0};
    key.token = token;
    const Il2CppImageGlobalMetadata *imageMetadata = GetImageMetadata(image);
    const Il2CppCustomAttributeDataRange *res = (const Il2CppCustomAttributeDataRange *)bsearch(&key, attributeTypeRange + imageMetadata->customAttributeStart, image->customAttributeCount, sizeof(Il2CppCustomAttributeDataRange), CompareTokens);
    return reinterpret_cast<Il2CppMetadataCustomAttributeHandle>(res);
}
std::tuple<void *, void *> il2cpp::vm::GlobalMetadata::GetCustomAttributeDataRange(const Il2CppImage *image, uint32_t token)
{
    const Il2CppCustomAttributeDataRange *attributeTypeRange = MetadataOffset<const Il2CppCustomAttributeDataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataRangeOffset + 484), 0);
    Il2CppCustomAttributeDataRange key = {0};
    key.token = token;
    const Il2CppImageGlobalMetadata *imageMetadata = GetImageMetadata(image);
    const Il2CppCustomAttributeDataRange *res = (const Il2CppCustomAttributeDataRange *)bsearch(&key, attributeTypeRange + imageMetadata->customAttributeStart, image->customAttributeCount, sizeof(Il2CppCustomAttributeDataRange), CompareTokens);
    if (res == NULL)
        return std::make_tuple<void *, void *>(NULL, NULL);
    const Il2CppCustomAttributeDataRange *next = res + 1;
    return std::make_tuple<void *, void *>(MetadataOffset<uint8_t *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataOffset + 484), res->startOffset), MetadataOffset<uint8_t *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataOffset + 484), next->startOffset));
}
CustomAttributesCache *il2cpp::vm::GlobalMetadata::GenerateCustomAttributesCache(const Il2CppImage *image, uint32_t token) { return GenerateCustomAttributesCacheInternal(GetImageMetadata(image), GetCustomAttributeIndex(image, token)); }
static bool HasAttributeFromTypeRange(const Il2CppImage *image, const Il2CppCustomAttributeDataRange *dataRange, Il2CppClass *attribute)
{
    void *start = MetadataOffset<uint8_t *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataOffset + 484), dataRange->startOffset);
    void *end = MetadataOffset<uint8_t *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataOffset + 484), (dataRange + 1)->startOffset);
    il2cpp::metadata::CustomAttributeDataReader reader(start, end);
    const MethodInfo *ctor;
    il2cpp::metadata::CustomAttributeCtorIterator iter = reader.GetCtorIterator();
    while (reader.IterateAttributeCtors(image, &ctor, &iter))
    {
        Il2CppClass *klass = ctor->klass;
        if (il2cpp::vm::Class::HasParent(klass, attribute) || (il2cpp::vm::Class::IsInterface(attribute) && il2cpp::vm::Class::IsAssignableFrom(attribute, klass)))
            return true;
    }
    return false;
}
bool il2cpp::vm::GlobalMetadata::HasAttribute(Il2CppMetadataCustomAttributeHandle token, Il2CppClass *attribute)
{
    if (token == NULL)
        return false;
    const Il2CppCustomAttributeDataRange *dataRange = reinterpret_cast<const Il2CppCustomAttributeDataRange *>(token);
    CustomAttributeIndex index = GetCustomAttributeIndex(dataRange);
    const Il2CppImageGlobalMetadata *imageMetadata = GetImageForCustomAttributeIndex(index);
    if (imageMetadata == NULL)
        return false;
    return HasAttributeFromTypeRange(imageMetadata->image, dataRange, attribute);
}
bool il2cpp::vm::GlobalMetadata::HasAttribute(const Il2CppImage *image, uint32_t token, Il2CppClass *attribute)
{
    CustomAttributeIndex index = GetCustomAttributeIndex(image, token);
    if (index == kCustomAttributeIndexInvalid)
        return false;
    const Il2CppCustomAttributeDataRange *attributeTypeRange = MetadataOffset<const Il2CppCustomAttributeDataRange *>(s_GlobalMetadata, (s_GlobalMetadataHeader->attributeDataRangeOffset + 484), index);
    return HasAttributeFromTypeRange(image, attributeTypeRange, attribute);
}
const MethodInfo *il2cpp::vm::GlobalMetadata::GetMethodInfoFromVTableSlot(const Il2CppClass *klass, int32_t vTableSlot)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    uint32_t index = typeDefinition->vtableStart + vTableSlot;
    const EncodedMethodIndex *vTableMethodReferences = (const EncodedMethodIndex *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->vtableMethodsOffset + 484));
    EncodedMethodIndex vTableMethodReference = vTableMethodReferences[index];
    return GetMethodInfoFromEncodedIndex(vTableMethodReference);
}
static int CompareFieldDefaultValues(const void *pkey, const void *pelem) { return (int)(((Il2CppFieldDefaultValue *)pkey)->fieldIndex - ((Il2CppFieldDefaultValue *)pelem)->fieldIndex); }
static const Il2CppFieldDefaultValue *GetFieldDefaultValueEntry(const FieldInfo *field)
{
    Il2CppClass *parent = field->parent;
    FieldIndex fieldIndex = (FieldIndex)(field - parent->fields);
    if (il2cpp::vm::Type::IsGenericInstance(&parent->byval_arg))
        parent = il2cpp::vm::GenericClass::GetTypeDefinition(parent->generic_class);
    fieldIndex += reinterpret_cast<const Il2CppTypeDefinition *>(parent->typeMetadataHandle)->fieldStart;
    Il2CppFieldDefaultValue key;
    key.fieldIndex = fieldIndex;
    const Il2CppFieldDefaultValue *start = (const Il2CppFieldDefaultValue *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->fieldDefaultValuesOffset + 484));
    const Il2CppFieldDefaultValue *res = (const Il2CppFieldDefaultValue *)bsearch(&key, start, s_GlobalMetadataHeader->fieldDefaultValuesSize / sizeof(Il2CppFieldDefaultValue), sizeof(Il2CppFieldDefaultValue), CompareFieldDefaultValues);
    return res;
}
static const uint8_t *GetFieldOrParameterDefalutValue(uint32_t index)
{
    if (index == kDefaultValueIndexNull)
        return NULL;
    const uint8_t *defaultValuesData = (const uint8_t *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->fieldAndParameterDefaultValueDataOffset + 484));
    return defaultValuesData + index;
}
const uint8_t *il2cpp::vm::GlobalMetadata::GetFieldDefaultValue(const FieldInfo *field, const Il2CppType **type)
{
    const Il2CppFieldDefaultValue *entry = GetFieldDefaultValueEntry(field);
    if (entry != NULL)
    {
        *type = GetIl2CppTypeFromIndex(entry->typeIndex);
        return GetFieldOrParameterDefalutValue(entry->dataIndex);
    }
    return NULL;
}
static int CompareParameterDefaultValues(const void *pkey, const void *pelem) { return (int)(((Il2CppParameterDefaultValue *)pkey)->parameterIndex - ((Il2CppParameterDefaultValue *)pelem)->parameterIndex); }
static const Il2CppParameterDefaultValue *GetParameterDefaultValueEntry(const MethodInfo *method, int32_t parameterPosition)
{
    if (il2cpp::vm::Method::IsGenericInstance(method))
        method = il2cpp::vm::MetadataCache::GetGenericMethodDefinition(method);
    const Il2CppMethodDefinition *methodDefinition = reinterpret_cast<const Il2CppMethodDefinition *>(method->methodMetadataHandle);
    if (methodDefinition == NULL)
        return NULL;
    ParameterIndex parameterIndex = methodDefinition->parameterStart + parameterPosition;
    Il2CppParameterDefaultValue key;
    key.parameterIndex = parameterIndex;
    const Il2CppParameterDefaultValue *start = (const Il2CppParameterDefaultValue *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->parameterDefaultValuesOffset + 484));
    const Il2CppParameterDefaultValue *res = (const Il2CppParameterDefaultValue *)bsearch(&key, start, s_GlobalMetadataHeader->parameterDefaultValuesSize / sizeof(Il2CppParameterDefaultValue), sizeof(Il2CppParameterDefaultValue), CompareParameterDefaultValues);
    return res;
}
const uint8_t *il2cpp::vm::GlobalMetadata::GetParameterDefaultValue(const MethodInfo *method, int32_t parameterPosition, const Il2CppType **type, bool *isExplicitySetNullDefaultValue)
{
    *isExplicitySetNullDefaultValue = false;
    const Il2CppParameterDefaultValue *parameterDefaultValue = GetParameterDefaultValueEntry(method, parameterPosition);
    if (parameterDefaultValue != NULL)
    {
        *type = GetIl2CppTypeFromIndex(parameterDefaultValue->typeIndex);
        *isExplicitySetNullDefaultValue = parameterDefaultValue->dataIndex == kDefaultValueIndexNull;
        return GetFieldOrParameterDefalutValue(parameterDefaultValue->dataIndex);
    }
    return NULL;
}
static TypeDefinitionIndex GetIndexForTypeDefinition(const Il2CppClass *klass)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    return GetIndexForTypeDefinitionInternal(typeDefinition);
}
uint32_t il2cpp::vm::GlobalMetadata::GetFieldOffset(const Il2CppClass *klass, int32_t fieldIndexInType, FieldInfo *field)
{
    uint32_t typeIndex = GetIndexForTypeDefinition(klass);
    int32_t offset = s_Il2CppMetadataRegistration->fieldOffsets[typeIndex][fieldIndexInType];
    return offset;
}
static int CompareFieldMarshaledSize(const void *pkey, const void *pelem) { return (int)(((Il2CppFieldMarshaledSize *)pkey)->fieldIndex - ((Il2CppFieldMarshaledSize *)pelem)->fieldIndex); }
int il2cpp::vm::GlobalMetadata::GetFieldMarshaledSizeForField(const FieldInfo *field)
{
    Il2CppClass *parent = field->parent;
    size_t fieldIndex = (field - parent->fields);
    if (il2cpp::vm::Type::IsGenericInstance(&parent->byval_arg))
        parent = il2cpp::vm::GenericClass::GetTypeDefinition(parent->generic_class);
    fieldIndex += reinterpret_cast<const Il2CppTypeDefinition *>(parent->typeMetadataHandle)->fieldStart;
    const Il2CppFieldMarshaledSize *start = (const Il2CppFieldMarshaledSize *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->fieldMarshaledSizesOffset + 484));
    Il2CppFieldMarshaledSize key;
    key.fieldIndex = (FieldIndex)fieldIndex;
    const Il2CppFieldMarshaledSize *res = (const Il2CppFieldMarshaledSize *)bsearch(&key, start, s_GlobalMetadataHeader->fieldMarshaledSizesSize / sizeof(Il2CppFieldMarshaledSize), sizeof(Il2CppFieldMarshaledSize), CompareFieldMarshaledSize);
    if (res != NULL)
        return res->size;
    return -1;
}
static const Il2CppFieldDefinition *GetFieldDefinitionFromIndex(const Il2CppImage *image, FieldIndex index)
{
    const Il2CppFieldDefinition *fields = (const Il2CppFieldDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->fieldsOffset + 484));
    return fields + index;
}
Il2CppMetadataFieldInfo il2cpp::vm::GlobalMetadata::GetFieldInfo(const Il2CppClass *klass, TypeFieldIndex fieldIndex)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    const Il2CppFieldDefinition *fieldDefinition = GetFieldDefinitionFromIndex(klass->image, typeDefinition->fieldStart + fieldIndex);
    return {GetIl2CppTypeFromIndex(fieldDefinition->typeIndex), GetStringFromIndex(fieldDefinition->nameIndex), fieldDefinition->token};
}
Il2CppMetadataMethodInfo il2cpp::vm::GlobalMetadata::GetMethodInfo(const Il2CppClass *klass, TypeMethodIndex index)
{
    const Il2CppTypeDefinition *typeDefinition = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    const Il2CppMethodDefinition *methodDefinition = GetMethodDefinitionFromIndex(typeDefinition->methodStart + index);
    return {
        reinterpret_cast<Il2CppMetadataMethodDefinitionHandle>(methodDefinition),
        GetStringFromIndex(methodDefinition->nameIndex),
        GetIl2CppTypeFromIndex(methodDefinition->returnType),
        methodDefinition->token,
        methodDefinition->flags,
        methodDefinition->iflags,
        methodDefinition->slot,
        methodDefinition->parameterCount,
    };
}
Il2CppMetadataParameterInfo il2cpp::vm::GlobalMetadata::GetParameterInfo(const Il2CppClass *klass, Il2CppMetadataMethodDefinitionHandle handle, MethodParameterIndex paramIndex)
{
    const Il2CppMethodDefinition *methodDefinition = reinterpret_cast<const Il2CppMethodDefinition *>(handle);
    const Il2CppParameterDefinition *parameterDefinition = GetParameterDefinitionFromIndex(klass->image, methodDefinition->parameterStart + paramIndex);
    return {
        GetStringFromIndex(parameterDefinition->nameIndex),
        parameterDefinition->token,
        GetIl2CppTypeFromIndex(parameterDefinition->typeIndex),
    };
}
Il2CppMetadataPropertyInfo il2cpp::vm::GlobalMetadata::GetPropertyInfo(const Il2CppClass *klass, TypePropertyIndex index)
{
    const Il2CppTypeDefinition *typeDefintion = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    const Il2CppPropertyDefinition *propertyDefintion = GetPropertyDefinitionFromIndex(klass->image, typeDefintion->propertyStart + index);
    return {
        GetStringFromIndex(propertyDefintion->nameIndex),
        propertyDefintion->get != kMethodIndexInvalid ? klass->methods[propertyDefintion->get] : NULL,
        propertyDefintion->set != kMethodIndexInvalid ? klass->methods[propertyDefintion->set] : NULL,
        propertyDefintion->attrs,
        propertyDefintion->token,
    };
}
Il2CppMetadataEventInfo il2cpp::vm::GlobalMetadata::GetEventInfo(const Il2CppClass *klass, TypeEventIndex index)
{
    const Il2CppTypeDefinition *typeDefintion = reinterpret_cast<const Il2CppTypeDefinition *>(klass->typeMetadataHandle);
    const Il2CppEventDefinition *eventDefintion = GetEventDefinitionFromIndex(klass->image, typeDefintion->eventStart + index);
    return {
        GetStringFromIndex(eventDefintion->nameIndex),
        GetIl2CppTypeFromIndex(eventDefintion->typeIndex),
        eventDefintion->add != kMethodIndexInvalid ? klass->methods[eventDefintion->add] : NULL,
        eventDefintion->remove != kMethodIndexInvalid ? klass->methods[eventDefintion->remove] : NULL,
        eventDefintion->raise != kMethodIndexInvalid ? klass->methods[eventDefintion->raise] : NULL,
        eventDefintion->token,
    };
}
uint32_t il2cpp::vm::GlobalMetadata::GetReturnParameterToken(Il2CppMetadataMethodDefinitionHandle handle)
{
    const Il2CppMethodDefinition *methodDefinition = reinterpret_cast<const Il2CppMethodDefinition *>(handle);
    return methodDefinition->returnParameterToken;
}
static const Il2CppGenericContainer *GetGenericContainerFromIndexInternal(GenericContainerIndex index)
{
    if (index == kGenericContainerIndexInvalid)
        return NULL;
    const Il2CppGenericContainer *genericContainers = (const Il2CppGenericContainer *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->genericContainersOffset + 484));
    return genericContainers + index;
}
static Il2CppMetadataGenericContainerHandle GetGenericContainerFromIndex(GenericContainerIndex index)
{
    const Il2CppGenericContainer *container = GetGenericContainerFromIndexInternal(index);
    return reinterpret_cast<Il2CppMetadataGenericContainerHandle>(container);
}
Il2CppMetadataGenericContainerHandle il2cpp::vm::GlobalMetadata::GetGenericContainerFromGenericClass(const Il2CppGenericClass *genericClass)
{
    const Il2CppTypeDefinition *genericType = reinterpret_cast<const Il2CppTypeDefinition *>(GetTypeHandleFromType(genericClass->type));
    return GetGenericContainerFromIndex(genericType->genericContainerIndex);
}
Il2CppMetadataGenericContainerHandle il2cpp::vm::GlobalMetadata::GetGenericContainerFromMethod(Il2CppMetadataMethodDefinitionHandle handle)
{
    const Il2CppMethodDefinition *methodDefinition = reinterpret_cast<const Il2CppMethodDefinition *>(handle);
    return GetGenericContainerFromIndex(methodDefinition->genericContainerIndex);
}
const Il2CppGenericMethod *il2cpp::vm::GlobalMetadata::GetGenericMethodFromTokenMethodTuple(const Il2CppTokenIndexMethodTuple *tuple) { return GetGenericMethodFromIndex(tuple->__genericMethodIndex); }
static Il2CppMetadataGenericParameterHandle GetGenericParameterFromIndexInternal(GenericParameterIndex index)
{
    if (index == kGenericParameterIndexInvalid)
        return NULL;
    const Il2CppGenericParameter *genericParameters = (const Il2CppGenericParameter *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->genericParametersOffset + 484));
    return reinterpret_cast<Il2CppMetadataGenericParameterHandle>(genericParameters + index);
}
Il2CppMetadataGenericParameterHandle il2cpp::vm::GlobalMetadata::GetGenericParameterFromType(const Il2CppType *type) { return type->data.genericParameterHandle; }
Il2CppClass *il2cpp::vm::GlobalMetadata::GetContainerDeclaringType(Il2CppMetadataGenericContainerHandle handle)
{
    const Il2CppGenericContainer *genericContainer = reinterpret_cast<const Il2CppGenericContainer *>(handle);
    if (genericContainer->is_method)
        return GetMethodInfoFromMethodDefinitionIndex(genericContainer->ownerIndex)->klass;
    return GetTypeInfoFromTypeDefinitionIndex(genericContainer->ownerIndex);
}
Il2CppClass *il2cpp::vm::GlobalMetadata::GetParameterDeclaringType(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    const Il2CppGenericContainer *genericContainer = GetGenericContainerFromIndexInternal(genericParameter->ownerIndex);
    if (genericContainer->is_method)
        return GetMethodInfoFromMethodDefinitionIndex(genericContainer->ownerIndex)->klass;
    return GetTypeInfoFromTypeDefinitionIndex(genericContainer->ownerIndex);
}
const MethodInfo *il2cpp::vm::GlobalMetadata::GetParameterDeclaringMethod(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    const Il2CppGenericContainer *genericContainer = GetGenericContainerFromIndexInternal(genericParameter->ownerIndex);
    if (genericContainer->is_method)
        return GetMethodInfoFromMethodDefinitionIndex(genericContainer->ownerIndex);
    return NULL;
}
Il2CppMetadataGenericParameterHandle il2cpp::vm::GlobalMetadata::GetGenericParameterFromIndex(Il2CppMetadataGenericContainerHandle handle, GenericContainerParameterIndex index)
{
    const Il2CppGenericContainer *genericContainer = reinterpret_cast<const Il2CppGenericContainer *>(handle);
    return GetGenericParameterFromIndexInternal(genericContainer->genericParameterStart + index);
}
const Il2CppType *il2cpp::vm::GlobalMetadata::GetGenericParameterConstraintFromIndex(Il2CppMetadataGenericParameterHandle handle, GenericParameterConstraintIndex index)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    index = genericParameter->constraintsStart + index;
    const TypeIndex *constraintIndices = (const TypeIndex *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->genericParameterConstraintsOffset + 484));
    return GetIl2CppTypeFromIndex(constraintIndices[index]);
}
static GenericParameterIndex GetIndexForGenericParameter(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    const Il2CppGenericParameter *genericParameters = (const Il2CppGenericParameter *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->genericParametersOffset + 484));
    ptrdiff_t index = genericParameter - genericParameters;
    return static_cast<GenericParameterIndex>(index);
}
const MethodInfo *il2cpp::vm::GlobalMetadata::GetGenericInstanceMethod(const MethodInfo *genericMethodDefinition, const Il2CppGenericContext *context)
{
    const MethodInfo *method = genericMethodDefinition;
    const Il2CppGenericInst *classInst = context->class_inst;
    const Il2CppGenericInst *methodInst = context->method_inst;
    if (genericMethodDefinition->is_inflated)
    {
        classInst = genericMethodDefinition->klass->generic_class->context.class_inst;
        method = genericMethodDefinition->genericMethod->methodDefinition;
    }
    return il2cpp::metadata::GenericMethod::GetMethod(method, classInst, methodInst);
}
const Il2CppType *il2cpp::vm::GlobalMetadata::GetTypeFromRgctxDefinition(const Il2CppRGCTXDefinition *rgctxDef) { return GetIl2CppTypeFromIndex(((const Il2CppRGCTXDefinitionData *)rgctxDef->data)->__typeIndex); }
const Il2CppGenericMethod *il2cpp::vm::GlobalMetadata::GetGenericMethodFromRgctxDefinition(const Il2CppRGCTXDefinition *rgctxDef) { return GetGenericMethodFromIndex(((const Il2CppRGCTXDefinitionData *)rgctxDef->data)->__methodIndex); }
std::pair<const Il2CppType *, const MethodInfo *> il2cpp::vm::GlobalMetadata::GetConstrainedCallFromRgctxDefinition(const Il2CppRGCTXDefinition *rgctxDef)
{
    const Il2CppRGCTXConstrainedData *constrainedData = (const Il2CppRGCTXConstrainedData *)rgctxDef->data;
    const Il2CppType *type = GetIl2CppTypeFromIndex(constrainedData->__typeIndex);
    const MethodInfo *method = GetMethodInfoFromEncodedIndex(constrainedData->__encodedMethodIndex);
    return std::make_pair(type, method);
}
enum PackingSize
{
    Zero,
    One,
    Two,
    Four,
    Eight,
    Sixteen,
    ThirtyTwo,
    SixtyFour,
    OneHundredTwentyEight
};
static uint8_t ConvertPackingSizeEnumToValue(PackingSize packingSize)
{
    switch (packingSize)
    {
    case Zero:
        return 0;
    case One:
        return 1;
    case Two:
        return 2;
    case Four:
        return 4;
    case Eight:
        return 8;
    case Sixteen:
        return 16;
    case ThirtyTwo:
        return 32;
    case SixtyFour:
        return 64;
    case OneHundredTwentyEight:
        return 128;
    default:
        return 0;
    }
}
int32_t il2cpp::vm::GlobalMetadata::StructLayoutPack(Il2CppMetadataTypeHandle handle) { return ConvertPackingSizeEnumToValue(static_cast<PackingSize>((reinterpret_cast<const Il2CppTypeDefinition *>(handle)->bitfield >> (kSpecifiedPackingSize - 1)) & 0xF)); }
static const Il2CppImage *GetImageForTypeDefinitionIndex(TypeDefinitionIndex index)
{
    for (int32_t imageIndex = 0; imageIndex < s_MetadataImagesCount; imageIndex++)
    {
        const Il2CppImageGlobalMetadata *imageMetadata = s_MetadataImagesTable + imageIndex;
        if (index >= imageMetadata->typeStart && static_cast<uint32_t>(index) < (imageMetadata->typeStart + imageMetadata->image->typeCount))
            return imageMetadata->image;
    }
    return NULL;
}
static Il2CppClass *FromTypeDefinition(TypeDefinitionIndex index)
{
    const Il2CppTypeDefinition *typeDefinitions = (const Il2CppTypeDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->typeDefinitionsOffset + 484));
    const Il2CppTypeDefinition *typeDefinition = typeDefinitions + index;
    const Il2CppTypeDefinitionSizes *typeDefinitionSizes = s_Il2CppMetadataRegistration->typeDefinitionsSizes[index];
    Il2CppClass *typeInfo = (Il2CppClass *)IL2CPP_CALLOC(1, sizeof(Il2CppClass) + (sizeof(VirtualInvokeData) * typeDefinition->vtable_count));
    typeInfo->klass = typeInfo;
    typeInfo->image = GetImageForTypeDefinitionIndex(index);
    typeInfo->name = GetStringFromIndex(typeDefinition->nameIndex);
    typeInfo->namespaze = GetStringFromIndex(typeDefinition->namespaceIndex);
    typeInfo->byval_arg = *il2cpp::vm::GlobalMetadata::GetIl2CppTypeFromIndex(typeDefinition->byvalTypeIndex);
    typeInfo->this_arg = typeInfo->byval_arg;
    typeInfo->this_arg.byref = true;
    typeInfo->this_arg.valuetype = 0;
    typeInfo->typeMetadataHandle = reinterpret_cast<const Il2CppMetadataTypeHandle>(typeDefinition);
    typeInfo->genericContainerHandle = GetGenericContainerFromIndex(typeDefinition->genericContainerIndex);
    typeInfo->instance_size = typeDefinitionSizes->instance_size;
    typeInfo->actualSize = typeDefinitionSizes->instance_size;
    typeInfo->native_size = typeDefinitionSizes->native_size;
    typeInfo->static_fields_size = typeDefinitionSizes->static_fields_size;
    typeInfo->thread_static_fields_size = typeDefinitionSizes->thread_static_fields_size;
    typeInfo->thread_static_fields_offset = -1;
    typeInfo->flags = typeDefinition->flags;
    typeInfo->enumtype = (typeDefinition->bitfield >> (kBitIsEnum - 1)) & 0x1;
    typeInfo->is_generic = typeDefinition->genericContainerIndex != kGenericContainerIndexInvalid;
    typeInfo->has_finalize = (typeDefinition->bitfield >> (kBitHasFinalizer - 1)) & 0x1;
    typeInfo->has_cctor = (typeDefinition->bitfield >> (kBitHasStaticConstructor - 1)) & 0x1;
    typeInfo->cctor_finished_or_no_cctor = !typeInfo->has_cctor;
    typeInfo->is_blittable = (typeDefinition->bitfield >> (kBitIsBlittable - 1)) & 0x1;
    typeInfo->is_import_or_windows_runtime = (typeDefinition->bitfield >> (kBitIsImportOrWindowsRuntime - 1)) & 0x1;
    typeInfo->packingSize = ConvertPackingSizeEnumToValue(static_cast<PackingSize>((typeDefinition->bitfield >> (kPackingSize - 1)) & 0xF));
    typeInfo->is_byref_like = (typeDefinition->bitfield >> (kBitIsByRefLike - 1)) & 0x1;
    typeInfo->method_count = typeDefinition->method_count;
    typeInfo->property_count = typeDefinition->property_count;
    typeInfo->field_count = typeDefinition->field_count;
    typeInfo->event_count = typeDefinition->event_count;
    typeInfo->nested_type_count = typeDefinition->nested_type_count;
    typeInfo->vtable_count = typeDefinition->vtable_count;
    typeInfo->interfaces_count = typeDefinition->interfaces_count;
    typeInfo->interface_offsets_count = typeDefinition->interface_offsets_count;
    typeInfo->token = typeDefinition->token;
    typeInfo->interopData = il2cpp::vm::MetadataCache::GetInteropDataForType(&typeInfo->byval_arg);
    if (typeDefinition->parentIndex != kTypeIndexInvalid)
        typeInfo->parent = il2cpp::vm::Class::FromIl2CppType(il2cpp::vm::GlobalMetadata::GetIl2CppTypeFromIndex(typeDefinition->parentIndex));
    if (typeDefinition->declaringTypeIndex != kTypeIndexInvalid)
        typeInfo->declaringType = il2cpp::vm::Class::FromIl2CppType(il2cpp::vm::GlobalMetadata::GetIl2CppTypeFromIndex(typeDefinition->declaringTypeIndex));
    typeInfo->castClass = typeInfo->element_class = typeInfo;
    if (typeInfo->enumtype)
        typeInfo->castClass = typeInfo->element_class = il2cpp::vm::Class::FromIl2CppType(il2cpp::vm::GlobalMetadata::GetIl2CppTypeFromIndex(typeDefinition->elementTypeIndex));
    return typeInfo;
}
const Il2CppType *il2cpp::vm::GlobalMetadata::GetIl2CppTypeFromIndex(TypeIndex index)
{
    if (index == kTypeIndexInvalid)
        return NULL;
    return s_Il2CppMetadataRegistration->types[index];
}
uint32_t il2cpp::vm::GlobalMetadata::GetGenericContainerCount(Il2CppMetadataGenericContainerHandle handle)
{
    const Il2CppGenericContainer *container = reinterpret_cast<const Il2CppGenericContainer *>(handle);
    return container != NULL ? container->type_argc : 0;
}
void il2cpp::vm::GlobalMetadata::MakeGenericArgType(Il2CppMetadataGenericContainerHandle containerHandle, Il2CppMetadataGenericParameterHandle paramHandle, Il2CppType *arg)
{
    const Il2CppGenericContainer *container = reinterpret_cast<const Il2CppGenericContainer *>(containerHandle);
    arg->type = container->is_method ? IL2CPP_TYPE_MVAR : IL2CPP_TYPE_VAR;
    arg->data.genericParameterHandle = paramHandle;
}
bool il2cpp::vm::GlobalMetadata::GetGenericContainerIsMethod(Il2CppMetadataGenericContainerHandle handle)
{
    const Il2CppGenericContainer *container = reinterpret_cast<const Il2CppGenericContainer *>(handle);
    return container != NULL ? container->is_method : false;
}
int16_t il2cpp::vm::GlobalMetadata::GetGenericConstraintCount(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    return genericParameter->constraintsCount;
}
const char *il2cpp::vm::GlobalMetadata::GetGenericParameterName(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    return GetStringFromIndex(genericParameter->nameIndex);
}
Il2CppGenericParameterInfo il2cpp::vm::GlobalMetadata::GetGenericParameterInfo(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    return {reinterpret_cast<Il2CppMetadataGenericContainerHandle>(GetGenericContainerFromIndexInternal(genericParameter->ownerIndex)), GetStringFromIndex(genericParameter->nameIndex), genericParameter->num, genericParameter->flags};
}
uint16_t il2cpp::vm::GlobalMetadata::GetGenericParameterFlags(Il2CppMetadataGenericParameterHandle handle)
{
    const Il2CppGenericParameter *genericParameter = reinterpret_cast<const Il2CppGenericParameter *>(handle);
    return genericParameter->flags;
}
const MethodInfo *il2cpp::vm::GlobalMetadata::GetMethodInfoFromCatchPoint(const Il2CppCatchPoint *cp) { return GetMethodInfoFromMethodDefinitionIndex(cp->__methodDefinitionIndex); }
const MethodInfo *il2cpp::vm::GlobalMetadata::GetMethodInfoFromSequencePoint(const Il2CppSequencePoint *seqPoint) { return GetMethodInfoFromMethodDefinitionIndex(seqPoint->__methodDefinitionIndex); }
Il2CppClass *il2cpp::vm::GlobalMetadata::GetTypeInfoFromTypeSourcePair(const Il2CppTypeSourceFilePair *pair) { return GetTypeInfoFromTypeDefinitionIndex(pair->__klassIndex); }
Il2CppClass *il2cpp::vm::GlobalMetadata::GetTypeInfoFromTypeIndex(TypeIndex index, bool throwOnError)
{
    if (index == kTypeIndexInvalid)
        return NULL;
    return utils::InitOnce(&s_TypeInfoTable[index], &g_MetadataLock, [index, throwOnError](il2cpp::os::FastAutoLock &_)
                           { const Il2CppType* type = s_Il2CppMetadataRegistration->types[index]; Il2CppClass *klass = Class::FromIl2CppType(type, throwOnError); if (klass != NULL) ClassInlines::InitFromCodegenSlow(klass, throwOnError); return klass; });
}
const MethodInfo *il2cpp::vm::GlobalMetadata::GetMethodInfoFromMethodHandle(Il2CppMetadataMethodDefinitionHandle handle)
{
    const Il2CppMethodDefinition *methodDefinition = reinterpret_cast<const Il2CppMethodDefinition *>(handle);
    const Il2CppMethodDefinition *methods = (const Il2CppMethodDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->methodsOffset + 484));
    const MethodIndex index = static_cast<MethodIndex>(methodDefinition - methods);
    return GetMethodInfoFromMethodDefinitionIndex(index);
}
#if IL2CPP_ENABLE_NATIVE_STACKTRACES
void il2cpp::vm::GlobalMetadata::GetAllManagedMethods(std::vector<MethodDefinitionKey> &managedMethods)
{
    size_t methodDefinitionsCount = s_GlobalMetadataHeader->methodsSize / sizeof(Il2CppMethodDefinition);
    managedMethods.reserve(methodDefinitionsCount + s_Il2CppMetadataRegistration->genericMethodTableCount);
    const Il2CppTypeDefinition *typeDefinitions = (const Il2CppTypeDefinition *)((const char *)s_GlobalMetadata + (s_GlobalMetadataHeader->typeDefinitionsOffset + 484));
    for (int32_t i = 0; i < s_MetadataImagesCount; i++)
    {
        const Il2CppImageGlobalMetadata *image = s_MetadataImagesTable + i;
        for (size_t j = 0; j < image->image->typeCount; j++)
        {
            const Il2CppTypeDefinition *type = typeDefinitions + image->typeStart + j;
            for (uint16_t u = 0; u < type->method_count; u++)
            {
                const Il2CppMethodDefinition *methodDefinition = GetMethodDefinitionFromIndex(type->methodStart + u);
                MethodDefinitionKey currentMethodList;
                currentMethodList.methodHandle = reinterpret_cast<Il2CppMetadataMethodDefinitionHandle>(methodDefinition);
                currentMethodList.method = il2cpp::vm::MetadataCache::GetMethodPointer(image->image, methodDefinition->token);
                if (currentMethodList.method)
                    managedMethods.push_back(currentMethodList);
            }
        }
    }
    for (int32_t i = 0; i < s_Il2CppMetadataRegistration->genericMethodTableCount; i++)
    {
        const Il2CppGenericMethodFunctionsDefinitions *genericMethodIndices = s_Il2CppMetadataRegistration->genericMethodTable + i;
        MethodDefinitionKey currentMethodList;
        GenericMethodIndex genericMethodIndex = genericMethodIndices->genericMethodIndex;
        const Il2CppMethodSpec *methodSpec = s_Il2CppMetadataRegistration->methodSpecs + genericMethodIndex;
        const Il2CppMethodDefinition *methodDefinition = GetMethodDefinitionFromIndex(methodSpec->methodDefinitionIndex);
        currentMethodList.methodHandle = reinterpret_cast<Il2CppMetadataMethodDefinitionHandle>(methodDefinition);
        currentMethodList.method = s_GlobalMetadata_CodeRegistration->genericMethodPointers[genericMethodIndices->indices.methodIndex];
        managedMethods.push_back(currentMethodList);
    }
}
#endif

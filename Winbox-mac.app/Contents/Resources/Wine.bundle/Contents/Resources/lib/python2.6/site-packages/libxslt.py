#
# Both libxml2mod and libxsltmod have a dependancy on libxml2.so
# and they should share the same module, try to convince the python
# loader to work in that mode if feasible
#
import sys
if not hasattr(sys,'getdlopenflags'):
    import libxml2mod
    import libxsltmod
    import libxml2
else:
    try:
        from dl import RTLD_GLOBAL, RTLD_NOW
    except ImportError:
        RTLD_GLOBAL = -1
        RTLD_NOW = -1
        try:
            import os
            osname = os.uname()[0]
            if osname == 'Linux' or osname == 'SunOS':
                RTLD_GLOBAL = 0x00100
                RTLD_NOW = 0x00002
            elif osname == 'Darwin':
                RTLD_GLOBAL = 0x8
                RTLD_NOW = 0x2
            #
            # is there a better method ?
            #
#            else:
#                print "libxslt could not guess RTLD_GLOBAL and RTLD_NOW " + \
#                      "on this platform: %s" % (osname)
        except:
             pass
#            print "libxslt could not guess RTLD_GLOBAL and RTLD_NOW " + \
#                  "on this platform: %s" % (osname)
    except:
        RTLD_GLOBAL = -1
        RTLD_NOW = -1

    if RTLD_GLOBAL != -1 and RTLD_NOW != -1:
        try:
            flags = sys.getdlopenflags() 
            sys.setdlopenflags(RTLD_GLOBAL | RTLD_NOW)
            try:
                import libxml2mod
                import libxsltmod
                import libxml2
            finally:
                sys.setdlopenflags(flags)
        except:
            import libxml2mod
            import libxsltmod
            import libxml2
    else:
        import libxml2mod
        import libxsltmod
        import libxml2


class transformCtxtBase:
    def __init__(self, _obj=None):
        if _obj != None: 
            self._o = _obj;
            return
        self._o = None
    def __hash__(self):
        v = libxsltmod.xsltGetTransformContextHashCode(self._o)
        return v
    def __eq__(self, other):
        if other == None:
            return 0
        v = libxsltmod.xsltCompareTransformContextsEqual(self._o, other._o)
        return v
        
class stylesheetBase:
    def __init__(self, _obj=None):
        if _obj != None: 
            self._o = _obj;
            return
        self._o = None
    def __hash__(self):
        v = libxsltmod.xsltGetStylesheetHashCode(self._o)
        return v
    def __eq__(self, other):
        if other == None:
            return 0
        v = libxsltmod.xsltCompareStylesheetsEqual(self._o, other._o)
        return v

class extensionModule:
    def _styleInit(self, style, URI):
        return self.styleInit(stylesheet(_obj=style), URI)

    def _styleShutdown(self, style, URI, data):
        return self.styleShutdown(stylesheet(_obj=style), URI, data)

    def _ctxtInit(self, ctxt, URI):
        return self.ctxtInit(transformCtxt(_obj=ctxt), URI)

    def _ctxtShutdown(self, ctxt, URI, data):
        return self.ctxtShutdown(transformCtxt(_obj=ctxt), URI, data)

    def styleInit(self, style, URI):
        """Callback function when used in a newly compiled stylesheet,
           the return value is passed in subsequent calls"""
        pass

    def styleShutdown(self, style, URI, data):
        """Callback function when a stylesheet using it is destroyed"""
        pass

    def ctxtInit(self, ctxt, URI):
        """Callback function when used in a new transformation process,
           the return value is passed in subsequent calls"""
        pass

    def ctxtShutdown(self, ctxt, URI, data):
        """Callback function when a transformation using it finishes"""
        pass

def cleanup():
    """Cleanup all libxslt and libxml2 memory allocated"""
    libxsltmod.xsltPythonCleanup()
    libxml2.cleanupParser()

#
# Everything below this point is automatically generated
#

#
# Functions from module extensions
#

def debugDumpExtensions(output):
    """Dumps a list of the registered XSLT extension functions and
       elements"""
    libxsltmod.xsltDebugDumpExtensions(output)

def initGlobals():
    """Initialize the global variables for extensions"""
    libxsltmod.xsltInitGlobals()

def registerTestModule():
    """Registers the test module"""
    libxsltmod.xsltRegisterTestModule()

def unregisterExtModule(URI):
    """Unregister an XSLT extension module from the library."""
    ret = libxsltmod.xsltUnregisterExtModule(URI)
    return ret

def unregisterExtModuleElement(name, URI):
    """Unregisters an extension module element"""
    ret = libxsltmod.xsltUnregisterExtModuleElement(name, URI)
    return ret

def unregisterExtModuleFunction(name, URI):
    """Unregisters an extension module function"""
    ret = libxsltmod.xsltUnregisterExtModuleFunction(name, URI)
    return ret

def unregisterExtModuleTopLevel(name, URI):
    """Unregisters an extension module top-level element"""
    ret = libxsltmod.xsltUnregisterExtModuleTopLevel(name, URI)
    return ret

#
# Functions from module extra
#

def registerAllExtras():
    """Registers the built-in extensions"""
    libxsltmod.xsltRegisterAllExtras()

#
# Functions from module python
#

def pythonCleanup():
    """Cleanup just libxslt (not libxml2) memory allocated"""
    libxsltmod.xsltPythonCleanup()

def registerErrorHandler(f, ctx):
    """Register a Python written function to for error reporting.
       The function is called back as f(ctx, error)."""
    ret = libxsltmod.xsltRegisterErrorHandler(f, ctx)
    return ret

def registerExtModuleElement(name, URI, precompile, transform):
    """Register a Python written element to the XSLT engine"""
    ret = libxsltmod.xsltRegisterExtModuleElement(name, URI, precompile, transform)
    return ret

def registerExtModuleFunction(name, URI, f):
    """Register a Python written function to the XSLT engine"""
    ret = libxsltmod.xsltRegisterExtModuleFunction(name, URI, f)
    return ret

def registerExtensionClass(URI, c):
    """Register a Python written extension class to the XSLT engine"""
    ret = libxsltmod.xsltRegisterExtensionClass(URI, c)
    return ret

def setLoaderFunc(loader):
    """Set the function for controlling document loading"""
    ret = libxsltmod.xsltSetLoaderFunc(loader)
    return ret

#
# Functions from module xslt
#

def cleanupGlobals():
    """Unregister all global variables set up by the XSLT library"""
    libxsltmod.xsltCleanupGlobals()

def init():
    """Initializes the processor (e.g. registers built-in
       extensions, etc.)"""
    libxsltmod.xsltInit()

#
# Functions from module xsltInternals
#

def isBlank(str):
    """Check if a string is ignorable"""
    ret = libxsltmod.xsltIsBlank(str)
    return ret

def loadStylesheetPI(doc):
    """This function tries to locate the stylesheet PI in the
      given document If found, and if contained within the
      document, it will extract that subtree to build the
      stylesheet to process @doc (doc itself will be modified).
      If found but referencing an external document it will
      attempt to load it and generate a stylesheet from it. In
      both cases, the resulting stylesheet and the document need
       to be freed once the transformation is done."""
    if doc == None: doc__o = None
    else: doc__o = doc._o
    ret = libxsltmod.xsltLoadStylesheetPI(doc__o)
    if ret == None: return None
    return stylesheet(_obj=ret)

def newStylesheet():
    """Create a new XSLT Stylesheet"""
    ret = libxsltmod.xsltNewStylesheet()
    if ret == None: return None
    return stylesheet(_obj=ret)

def parseStylesheetDoc(doc):
    """parse an XSLT stylesheet, building the associated
      structures.  doc is kept as a reference within the returned
      stylesheet, so changes to doc after the parsing will be
      reflected when the stylesheet is applied, and the doc is
       automatically freed when the stylesheet is closed."""
    if doc == None: doc__o = None
    else: doc__o = doc._o
    ret = libxsltmod.xsltParseStylesheetDoc(doc__o)
    if ret == None: return None
    return stylesheet(_obj=ret)

def parseStylesheetFile(filename):
    """Load and parse an XSLT stylesheet"""
    ret = libxsltmod.xsltParseStylesheetFile(filename)
    if ret == None: return None
    return stylesheet(_obj=ret)

def uninit():
    """Uninitializes the processor."""
    libxsltmod.xsltUninit()

#
# Functions from module xsltlocale
#

def freeLocales():
    """Cleanup function for the locale support on shutdown"""
    libxsltmod.xsltFreeLocales()

#
# Functions from module xsltutils
#

def calibrateAdjust(delta):
    """Used for to correct the calibration for xsltTimestamp()"""
    libxsltmod.xsltCalibrateAdjust(delta)

def debuggerStatus():
    """Get xslDebugStatus."""
    ret = libxsltmod.xsltGetDebuggerStatus()
    return ret

def nsProp(node, name, nameSpace):
    """Similar to xmlGetNsProp() but with a slightly different
      semantic  Search and get the value of an attribute
      associated to a node This attribute has to be anchored in
      the namespace specified, or has no namespace and the
      element is in that namespace.  This does the entity
      substitution. This function looks in DTD attribute
      declaration for #FIXED or default declaration values unless
       DTD use has been turned off."""
    if node == None: node__o = None
    else: node__o = node._o
    ret = libxsltmod.xsltGetNsProp(node__o, name, nameSpace)
    return ret

def setDebuggerStatus(value):
    """This function sets the value of xslDebugStatus."""
    libxsltmod.xsltSetDebuggerStatus(value)

def timestamp():
    """Used for gathering profiling data"""
    ret = libxsltmod.xsltTimestamp()
    return ret

def xslDropCall():
    """Drop the topmost item off the call stack"""
    libxsltmod.xslDropCall()

class xpathParserContext(libxml2.xpathParserContext):
    def __init__(self, _obj=None):
        self._o = None
        libxml2.xpathParserContext.__init__(self, _obj=_obj)

    # accessors for xpathParserContext
    def context(self):
        """Get the xpathContext from an xpathParserContext"""
        ret = libxsltmod.xsltXPathParserGetContext(self._o)
        if ret == None: return None
        return xpathContext(_obj=ret)

    #
    # xpathParserContext functions from module extra
    #

    def functionNodeSet(self, nargs):
        """Implement the node-set() XSLT function node-set
          node-set(result-tree)  This function is available in
           libxslt, saxon or xt namespace."""
        libxsltmod.xsltFunctionNodeSet(self._o, nargs)

    #
    # xpathParserContext functions from module functions
    #

    def documentFunction(self, nargs):
        """Implement the document() XSLT function node-set
           document(object, node-set?)"""
        libxsltmod.xsltDocumentFunction(self._o, nargs)

    def elementAvailableFunction(self, nargs):
        """Implement the element-available() XSLT function boolean
           element-available(string)"""
        libxsltmod.xsltElementAvailableFunction(self._o, nargs)

    def formatNumberFunction(self, nargs):
        """Implement the format-number() XSLT function string
           format-number(number, string, string?)"""
        libxsltmod.xsltFormatNumberFunction(self._o, nargs)

    def functionAvailableFunction(self, nargs):
        """Implement the function-available() XSLT function boolean
           function-available(string)"""
        libxsltmod.xsltFunctionAvailableFunction(self._o, nargs)

    def generateIdFunction(self, nargs):
        """Implement the generate-id() XSLT function string
           generate-id(node-set?)"""
        libxsltmod.xsltGenerateIdFunction(self._o, nargs)

    def keyFunction(self, nargs):
        """Implement the key() XSLT function node-set key(string,
           object)"""
        libxsltmod.xsltKeyFunction(self._o, nargs)

    def systemPropertyFunction(self, nargs):
        """Implement the system-property() XSLT function object
           system-property(string)"""
        libxsltmod.xsltSystemPropertyFunction(self._o, nargs)

    def unparsedEntityURIFunction(self, nargs):
        """Implement the unparsed-entity-uri() XSLT function string
           unparsed-entity-uri(string)"""
        libxsltmod.xsltUnparsedEntityURIFunction(self._o, nargs)

class xpathContext(libxml2.xpathContext):
    def __init__(self, _obj=None):
        self._o = None
        libxml2.xpathContext.__init__(self, _obj=_obj)

    def __del__(self):
        pass
    # accessors for xpathContext
    def transformContext(self):
        """Get the transformation context from an xpathContext"""
        ret = libxsltmod.xsltXPathGetTransformContext(self._o)
        if ret == None: return None
        return transformCtxt(_obj=ret)

    #
    # xpathContext functions from module functions
    #

    def registerAllFunctions(self):
        """Registers all default XSLT functions in this context"""
        libxsltmod.xsltRegisterAllFunctions(self._o)

class transformCtxt(transformCtxtBase):
    def __init__(self, _obj=None):
        self._o = None
        transformCtxtBase.__init__(self, _obj=_obj)

    # accessors for transformCtxt
    def context(self):
        """Get the XPath context of a transformation"""
        ret = libxsltmod.xsltTransformGetContext(self._o)
        if ret == None: return None
        return xpathContext(_obj=ret)

    def current(self):
        """Get the current() node of a transformation"""
        ret = libxsltmod.xsltTransformGetCurrent(self._o)
        if ret == None: return None
        return libxml2.xmlNode(_obj=ret)

    def insertNode(self):
        """Get the insertion node in the output document"""
        ret = libxsltmod.xsltTransformGetInsertNode(self._o)
        if ret == None: return None
        return libxml2.xmlNode(_obj=ret)

    def instruction(self):
        """Get the instruction node in the stylesheet"""
        ret = libxsltmod.xsltTransformGetInstruction(self._o)
        if ret == None: return None
        return libxml2.xmlNode(_obj=ret)

    def mode(self):
        """Get the mode of a transformation"""
        ret = libxsltmod.xsltTransformGetMode(self._o)
        return ret

    def modeURI(self):
        """Get the mode URI of a transformation"""
        ret = libxsltmod.xsltTransformGetModeURI(self._o)
        return ret

    def outputDoc(self):
        """Get the output document of a transformation"""
        ret = libxsltmod.xsltTransformGetOutputDoc(self._o)
        if ret == None: return None
        return libxml2.xmlDoc(_obj=ret)

    def outputURI(self):
        """Get the output URI of a transformation if known"""
        ret = libxsltmod.xsltTransformGetOutputURI(self._o)
        return ret

    def style(self):
        """Get the stylesheet from a transformation"""
        ret = libxsltmod.xsltTransformGetStyle(self._o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    #
    # transformCtxt functions from module attributes
    #

    def applyAttributeSet(self, node, inst, attrSets):
        """Apply the xsl:use-attribute-sets. If @attrSets is None,
          then @inst will be used to exctract this value. If both,
           @attrSets and @inst, are None, then this will do nothing."""
        if node == None: node__o = None
        else: node__o = node._o
        if inst == None: inst__o = None
        else: inst__o = inst._o
        libxsltmod.xsltApplyAttributeSet(self._o, node__o, inst__o, attrSets)

    #
    # transformCtxt functions from module documents
    #

    def freeDocuments(self):
        """Free up all the space used by the loaded documents"""
        libxsltmod.xsltFreeDocuments(self._o)

    #
    # transformCtxt functions from module extensions
    #

    def freeCtxtExts(self):
        """Free the XSLT extension data"""
        libxsltmod.xsltFreeCtxtExts(self._o)

    def initCtxtExts(self):
        """Initialize the set of modules with registered stylesheet
           data"""
        ret = libxsltmod.xsltInitCtxtExts(self._o)
        return ret

    def shutdownCtxtExts(self):
        """Shutdown the set of modules loaded"""
        libxsltmod.xsltShutdownCtxtExts(self._o)

    #
    # transformCtxt functions from module extra
    #

    def debug(self, node, inst, comp):
        """Process an debug node"""
        if node == None: node__o = None
        else: node__o = node._o
        if inst == None: inst__o = None
        else: inst__o = inst._o
        libxsltmod.xsltDebug(self._o, node__o, inst__o, comp)

    def registerExtras(self):
        """Registers the built-in extensions. This function is
           deprecated, use xsltRegisterAllExtras instead."""
        libxsltmod.xsltRegisterExtras(self._o)

    #
    # transformCtxt functions from module imports
    #

    def findElemSpaceHandling(self, node):
        """Find strip-space or preserve-space informations for an
           element respect the import precedence or the wildcards"""
        if node == None: node__o = None
        else: node__o = node._o
        ret = libxsltmod.xsltFindElemSpaceHandling(self._o, node__o)
        return ret

    def needElemSpaceHandling(self):
        """Checks whether that stylesheet requires white-space
           stripping"""
        ret = libxsltmod.xsltNeedElemSpaceHandling(self._o)
        return ret

    #
    # transformCtxt functions from module namespaces
    #

    def copyNamespace(self, elem, ns):
        """Copies a namespace node (declaration). If @elem is not
           None, then the new namespace will be declared on @elem."""
        if elem == None: elem__o = None
        else: elem__o = elem._o
        if ns == None: ns__o = None
        else: ns__o = ns._o
        ret = libxsltmod.xsltCopyNamespace(self._o, elem__o, ns__o)
        if ret == None: return None
        return libxml2.xmlNs(_obj=ret)

    def copyNamespaceList(self, node, cur):
        """Do a copy of an namespace list. If @node is non-None the
          new namespaces are added automatically. This handles
          namespaces aliases. This function is intended only for
          *internal* use at transformation-time for copying
          ns-declarations of Literal Result Elements.  Called by:
          xsltCopyTreeInternal() (transform.c) xsltShallowCopyElem()
          (transform.c)  REVISIT: This function won't be used in the
           refactored code."""
        if node == None: node__o = None
        else: node__o = node._o
        if cur == None: cur__o = None
        else: cur__o = cur._o
        ret = libxsltmod.xsltCopyNamespaceList(self._o, node__o, cur__o)
        if ret == None: return None
        return libxml2.xmlNs(_obj=ret)

    def namespace(self, cur, ns, out):
        """Find a matching (prefix and ns-name) ns-declaration for the
          requested @ns->prefix and @ns->href in the result tree. If
          none is found then a new ns-declaration will be added to
          @resultElem. If, in this case, the given prefix is already
          in use, then a ns-declaration with a modified ns-prefix be
          we created.  Called by: - xsltCopyPropList() (*not* 
          anymore) - xsltShallowCopyElement() -
          xsltCopyTreeInternal() (*not*  anymore) -
          xsltApplySequenceConstructor() (*not* in the refactored
           code), - xsltElement() (*not* anymore)"""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        if ns == None: ns__o = None
        else: ns__o = ns._o
        if out == None: out__o = None
        else: out__o = out._o
        ret = libxsltmod.xsltGetNamespace(self._o, cur__o, ns__o, out__o)
        if ret == None: return None
        return libxml2.xmlNs(_obj=ret)

    def plainNamespace(self, cur, ns, out):
        """Obsolete. *Not* called by any Libxslt/Libexslt function.
           Exaclty the same as xsltGetNamespace()."""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        if ns == None: ns__o = None
        else: ns__o = ns._o
        if out == None: out__o = None
        else: out__o = out._o
        ret = libxsltmod.xsltGetPlainNamespace(self._o, cur__o, ns__o, out__o)
        if ret == None: return None
        return libxml2.xmlNs(_obj=ret)

    def specialNamespace(self, invocNode, nsName, nsPrefix, target):
        """Find a matching (prefix and ns-name) ns-declaration for the
          requested @nsName and @nsPrefix in the result tree. If none
          is found then a new ns-declaration will be added to
          @resultElem. If, in this case, the given prefix is already
          in use, then a ns-declaration with a modified ns-prefix be
          we created. Note that this function's priority is to
          preserve ns-prefixes; it will only change a prefix if
          there's a namespace clash. If both @nsName and @nsPrefix
          are None, then this will try to "undeclare" a default
           namespace by declaring an xmlns=""."""
        if invocNode == None: invocNode__o = None
        else: invocNode__o = invocNode._o
        if target == None: target__o = None
        else: target__o = target._o
        ret = libxsltmod.xsltGetSpecialNamespace(self._o, invocNode__o, nsName, nsPrefix, target__o)
        if ret == None: return None
        return libxml2.xmlNs(_obj=ret)

    #
    # transformCtxt functions from module python
    #

    def compareTransformContextsEqual(self, other):
        """Compare one transformCtxt with another"""
        if other == None: other__o = None
        else: other__o = other._o
        ret = libxsltmod.xsltCompareTransformContextsEqual(self._o, other__o)
        return ret

    def freeTransformContext(self):
        """Free up an existing XSLT TransformContext"""
        libxsltmod.xsltFreeTransformContext(self._o)

    def transformContextHashCode(self):
        """Get the hash code of the transformContext"""
        ret = libxsltmod.xsltGetTransformContextHashCode(self._o)
        return ret

    #
    # transformCtxt functions from module templates
    #

    def attrListTemplateProcess(self, target, attrs):
        """Processes all attributes of a Literal Result Element.
          Attribute references are applied via xsl:use-attribute-set
          attributes. Copies all non XSLT-attributes over to the
          @target element and evaluates Attribute Value Templates. 
           Called by xsltApplySequenceConstructor() (transform.c)."""
        if target == None: target__o = None
        else: target__o = target._o
        if attrs == None: attrs__o = None
        else: attrs__o = attrs._o
        ret = libxsltmod.xsltAttrListTemplateProcess(self._o, target__o, attrs__o)
        if ret == None: return None
        return libxml2.xmlAttr(_obj=ret)

    def attrTemplateProcess(self, target, attr):
        """Process one attribute of a Literal Result Element (in the
          stylesheet). Evaluates Attribute Value Templates and copies
          the attribute over to the result element. This does *not*
           process attribute sets (xsl:use-attribute-set)."""
        if target == None: target__o = None
        else: target__o = target._o
        if attr == None: attr__o = None
        else: attr__o = attr._o
        ret = libxsltmod.xsltAttrTemplateProcess(self._o, target__o, attr__o)
        if ret == None: return None
        return libxml2.xmlAttr(_obj=ret)

    def attrTemplateValueProcess(self, str):
        """Process the given node and return the new string value."""
        ret = libxsltmod.xsltAttrTemplateValueProcess(self._o, str)
        return ret

    def attrTemplateValueProcessNode(self, str, inst):
        """Process the given string, allowing to pass a namespace
          mapping context and return the new string value.  Called
          by: - xsltAttrTemplateValueProcess() (templates.c) -
          xsltEvalAttrValueTemplate() (templates.c)  QUESTION: Why is
          this function public? It is not used outside of templates.c."""
        if inst == None: inst__o = None
        else: inst__o = inst._o
        ret = libxsltmod.xsltAttrTemplateValueProcessNode(self._o, str, inst__o)
        return ret

    def evalAttrValueTemplate(self, inst, name, ns):
        """Evaluate a attribute value template, i.e. the attribute
          value can contain expressions contained in curly braces
           ({}) and those are substituted by they computed value."""
        if inst == None: inst__o = None
        else: inst__o = inst._o
        ret = libxsltmod.xsltEvalAttrValueTemplate(self._o, inst__o, name, ns)
        return ret

    def evalTemplateString(self, contextNode, inst):
        """Processes the sequence constructor of the given instruction
          on @contextNode and converts the resulting tree to a
          string. This is needed by e.g. xsl:comment and
           xsl:processing-instruction."""
        if contextNode == None: contextNode__o = None
        else: contextNode__o = contextNode._o
        if inst == None: inst__o = None
        else: inst__o = inst._o
        ret = libxsltmod.xsltEvalTemplateString(self._o, contextNode__o, inst__o)
        return ret

    #
    # transformCtxt functions from module variables
    #

    def evalGlobalVariables(self):
        """Evaluates all global variables and parameters of a
          stylesheet. For internal use only. This is called at start
           of a transformation."""
        ret = libxsltmod.xsltEvalGlobalVariables(self._o)
        return ret

    def evalOneUserParam(self, name, value):
        """This is normally called from xsltEvalUserParams to process
          a single parameter from a list of parameters.  The @value
          is evaluated as an XPath expression and the result is
          stored in the context's global variable/parameter hash
          table.  To have a parameter treated literally (not as an
          XPath expression) use xsltQuoteUserParams (or
          xsltQuoteOneUserParam).  For more details see description
           of xsltProcessOneUserParamInternal."""
        ret = libxsltmod.xsltEvalOneUserParam(self._o, name, value)
        return ret

    def freeGlobalVariables(self):
        """Free up the data associated to the global variables its
           value."""
        libxsltmod.xsltFreeGlobalVariables(self._o)

    def parseStylesheetParam(self, cur):
        """Registers a local XSLT 'param' declaration at
           transformation time and evaluates its value."""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        libxsltmod.xsltParseStylesheetParam(self._o, cur__o)

    def parseStylesheetVariable(self, inst):
        """Registers a local XSLT 'variable' instruction at
           transformation time and evaluates its value."""
        if inst == None: inst__o = None
        else: inst__o = inst._o
        libxsltmod.xsltParseStylesheetVariable(self._o, inst__o)

    def quoteOneUserParam(self, name, value):
        """This is normally called from xsltQuoteUserParams to process
          a single parameter from a list of parameters.  The @value
          is stored in the context's global variable/parameter hash
           table."""
        ret = libxsltmod.xsltQuoteOneUserParam(self._o, name, value)
        return ret

    def variableLookup(self, name, ns_uri):
        """Search in the Variable array of the context for the given
           variable value."""
        ret = libxsltmod.xsltVariableLookup(self._o, name, ns_uri)
        if ret == None: return None
        return libxml2.xpathObjectRet(ret)

    #
    # transformCtxt functions from module xsltInternals
    #

    def allocateExtraCtxt(self):
        """Allocate an extra runtime information slot at run-time and
          return its number This make sure there is a slot ready in
           the transformation context"""
        ret = libxsltmod.xsltAllocateExtraCtxt(self._o)
        return ret

    def createRVT(self):
        """Creates a Result Value Tree (the XSLT 1.0 term for this is
           "Result Tree Fragment")"""
        ret = libxsltmod.xsltCreateRVT(self._o)
        if ret == None: return None
        return libxml2.xmlDoc(_obj=ret)

    def extensionInstructionResultFinalize(self):
        """Finalizes the data (e.g. result tree fragments) created
          within a value-returning process (e.g. EXSLT's function).
          Tree fragments marked as being returned by a function are
          set to normal state, which means that the fragment garbage
          collector will free them after the function-calling process
           exits."""
        ret = libxsltmod.xsltExtensionInstructionResultFinalize(self._o)
        return ret

    def freeRVTs(self):
        """Frees all registered result value trees (Result Tree
          Fragments) of the transformation. Internal function; should
           not be called by user-code."""
        libxsltmod.xsltFreeRVTs(self._o)

    def initAllDocKeys(self):
        """INTERNAL ROUTINE ONLY  Check if any keys on the current
           document need to be computed"""
        ret = libxsltmod.xsltInitAllDocKeys(self._o)
        return ret

    def registerLocalRVT(self, RVT):
        """Registers a result value tree (XSLT 1.0 term: Result Tree
          Fragment) in the RVT garbage collector. The fragment will
          be freed when the instruction which created the fragment
           exits."""
        if RVT == None: RVT__o = None
        else: RVT__o = RVT._o
        ret = libxsltmod.xsltRegisterLocalRVT(self._o, RVT__o)
        return ret

    def registerPersistRVT(self, RVT):
        """Register the result value tree (XSLT 1.0 term: Result Tree
          Fragment) in the fragment garbage collector. The fragment
           will be freed when the transformation context is freed."""
        if RVT == None: RVT__o = None
        else: RVT__o = RVT._o
        ret = libxsltmod.xsltRegisterPersistRVT(self._o, RVT__o)
        return ret

    def registerTmpRVT(self, RVT):
        """Registers the result value tree (XSLT 1.0 term: Result Tree
          Fragment) in the garbage collector. The fragment will be
          freed at the exit of the currently instantiated
          xsl:template. Obsolete; this function might produce massive
          memory overhead, since the fragment is only freed when the
          current xsl:template exits. Use xsltRegisterLocalRVT()
           instead."""
        if RVT == None: RVT__o = None
        else: RVT__o = RVT._o
        ret = libxsltmod.xsltRegisterTmpRVT(self._o, RVT__o)
        return ret

    def releaseRVT(self, RVT):
        """Either frees the RVT (which is an xmlDoc) or stores it in
           the context's cache for later reuse."""
        if RVT == None: RVT__o = None
        else: RVT__o = RVT._o
        libxsltmod.xsltReleaseRVT(self._o, RVT__o)

    #
    # transformCtxt functions from module xsltutils
    #

    def message(self, node, inst):
        """Process and xsl:message construct"""
        if node == None: node__o = None
        else: node__o = node._o
        if inst == None: inst__o = None
        else: inst__o = inst._o
        libxsltmod.xsltMessage(self._o, node__o, inst__o)

    def printErrorContext(self, style, node):
        """Display the context of an error."""
        if style == None: style__o = None
        else: style__o = style._o
        if node == None: node__o = None
        else: node__o = node._o
        libxsltmod.xsltPrintErrorContext(self._o, style__o, node__o)

    def profileInformation(self):
        """This function should be called after the transformation
          completed to extract template processing profiling
          informations if availble. The informations are returned as
          an XML document tree like <?xml version="1.0"?> <profile>
          <template rank="1" match="*" name="" mode="" calls="6"
          time="48" average="8"/> <template rank="2"
          match="item2|item3" name="" mode="" calls="10" time="30"
          average="3"/> <template rank="3" match="item1" name=""
          mode="" calls="5" time="17" average="3"/> </profile> The
          caller will need to free up the returned tree with
           xmlFreeDoc()"""
        ret = libxsltmod.xsltGetProfileInformation(self._o)
        if ret == None: return None
        return libxml2.xmlDoc(_obj=ret)

    def saveProfiling(self, output):
        """Save the profiling informations on @output"""
        libxsltmod.xsltSaveProfiling(self._o, output)

    def setCtxtParseOptions(self, options):
        """Change the default parser option passed by the XSLT engine
           to the parser when using document() loading."""
        ret = libxsltmod.xsltSetCtxtParseOptions(self._o, options)
        return ret

class stylesheet(stylesheetBase):
    def __init__(self, _obj=None):
        self._o = None
        stylesheetBase.__init__(self, _obj=_obj)

    # accessors for stylesheet
    def doc(self):
        """Get the document of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetDoc(self._o)
        if ret == None: return None
        return libxml2.xmlDoc(_obj=ret)

    def doctypePublic(self):
        """Get the output PUBLIC of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetDoctypePublic(self._o)
        return ret

    def doctypeSystem(self):
        """Get the output SYSTEM of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetDoctypeSystem(self._o)
        return ret

    def encoding(self):
        """Get the output encoding of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetEncoding(self._o)
        return ret

    def imports(self):
        """Get the imports of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetImports(self._o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    def method(self):
        """Get the output method of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetMethod(self._o)
        return ret

    def methodURI(self):
        """Get the output method URI of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetMethodURI(self._o)
        return ret

    def next(self):
        """Get the next sibling of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetNext(self._o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    def parent(self):
        """Get the parent of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetParent(self._o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    def version(self):
        """Get the output version of a stylesheet"""
        ret = libxsltmod.xsltStylesheetGetVersion(self._o)
        return ret

    #
    # stylesheet functions from module attributes
    #

    def freeAttributeSetsHashes(self):
        """Free up the memory used by attribute sets"""
        libxsltmod.xsltFreeAttributeSetsHashes(self._o)

    def parseStylesheetAttributeSet(self, cur):
        """parse an XSLT stylesheet attribute-set element"""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        libxsltmod.xsltParseStylesheetAttributeSet(self._o, cur__o)

    def resolveStylesheetAttributeSet(self):
        """resolve the references between attribute sets."""
        libxsltmod.xsltResolveStylesheetAttributeSet(self._o)

    #
    # stylesheet functions from module documents
    #

    def freeStyleDocuments(self):
        """Frees the node-trees (and xsltDocument structures) of all
          stylesheet-modules of the stylesheet-level represented by
           the given @style."""
        libxsltmod.xsltFreeStyleDocuments(self._o)

    #
    # stylesheet functions from module extensions
    #

    def checkExtPrefix(self, URI):
        """Check if the given prefix is one of the declared
          extensions. This is intended to be called only at
          compile-time. Called by: xsltGetInheritedNsList() (xslt.c)
           xsltParseTemplateContent (xslt.c)"""
        ret = libxsltmod.xsltCheckExtPrefix(self._o, URI)
        return ret

    def checkExtURI(self, URI):
        """Check if the given prefix is one of the declared
          extensions. This is intended to be called only at
          compile-time. Called by: xsltPrecomputeStylesheet()
           (xslt.c) xsltParseTemplateContent (xslt.c)"""
        ret = libxsltmod.xsltCheckExtURI(self._o, URI)
        return ret

    def freeExts(self):
        """Free up the memory used by XSLT extensions in a stylesheet"""
        libxsltmod.xsltFreeExts(self._o)

    def registerExtPrefix(self, prefix, URI):
        """Registers an extension namespace This is called from xslt.c
          during compile-time. The given prefix is not needed. Called
          by: xsltParseExtElemPrefixes() (new function)
           xsltRegisterExtPrefix() (old function)"""
        ret = libxsltmod.xsltRegisterExtPrefix(self._o, prefix, URI)
        return ret

    def shutdownExts(self):
        """Shutdown the set of modules loaded"""
        libxsltmod.xsltShutdownExts(self._o)

    #
    # stylesheet functions from module imports
    #

    def nextImport(self):
        """Find the next stylesheet in import precedence."""
        ret = libxsltmod.xsltNextImport(self._o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    def parseStylesheetImport(self, cur):
        """parse an XSLT stylesheet import element"""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        ret = libxsltmod.xsltParseStylesheetImport(self._o, cur__o)
        return ret

    def parseStylesheetInclude(self, cur):
        """parse an XSLT stylesheet include element"""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        ret = libxsltmod.xsltParseStylesheetInclude(self._o, cur__o)
        return ret

    #
    # stylesheet functions from module keys
    #

    def addKey(self, name, nameURI, match, use, inst):
        """add a key definition to a stylesheet"""
        if inst == None: inst__o = None
        else: inst__o = inst._o
        ret = libxsltmod.xsltAddKey(self._o, name, nameURI, match, use, inst__o)
        return ret

    def freeKeys(self):
        """Free up the memory used by XSLT keys in a stylesheet"""
        libxsltmod.xsltFreeKeys(self._o)

    #
    # stylesheet functions from module namespaces
    #

    def freeNamespaceAliasHashes(self):
        """Free up the memory used by namespaces aliases"""
        libxsltmod.xsltFreeNamespaceAliasHashes(self._o)

    def namespaceAlias(self, node):
        """Read the stylesheet-prefix and result-prefix attributes,
           register them as well as the corresponding namespace."""
        if node == None: node__o = None
        else: node__o = node._o
        libxsltmod.xsltNamespaceAlias(self._o, node__o)

    #
    # stylesheet functions from module pattern
    #

    def cleanupTemplates(self):
        """Cleanup the state of the templates used by the stylesheet
           and the ones it imports."""
        libxsltmod.xsltCleanupTemplates(self._o)

    def freeTemplateHashes(self):
        """Free up the memory used by xsltAddTemplate/xsltGetTemplate
           mechanism"""
        libxsltmod.xsltFreeTemplateHashes(self._o)

    #
    # stylesheet functions from module preproc
    #

    def freeStylePreComps(self):
        """Free up the memory allocated by all precomputed blocks"""
        libxsltmod.xsltFreeStylePreComps(self._o)

    def stylePreCompute(self, inst):
        """Precompute an XSLT stylesheet element"""
        if inst == None: inst__o = None
        else: inst__o = inst._o
        libxsltmod.xsltStylePreCompute(self._o, inst__o)

    #
    # stylesheet functions from module python
    #

    def applyStylesheet(self, doc, params):
        """Apply the stylesheet to the document"""
        if doc == None: doc__o = None
        else: doc__o = doc._o
        ret = libxsltmod.xsltApplyStylesheet(self._o, doc__o, params)
        if ret == None: return None
        return libxml2.xmlDoc(_obj=ret)

    def applyStylesheetUser(self, doc, params, transformCtxt):
        """Apply the stylesheet to the document"""
        if doc == None: doc__o = None
        else: doc__o = doc._o
        if transformCtxt == None: transformCtxt__o = None
        else: transformCtxt__o = transformCtxt._o
        ret = libxsltmod.xsltApplyStylesheetUser(self._o, doc__o, params, transformCtxt__o)
        if ret == None: return None
        return libxml2.xmlDoc(_obj=ret)

    def compareStylesheetsEqual(self, other):
        """Compare one stylesheet with another"""
        if other == None: other__o = None
        else: other__o = other._o
        ret = libxsltmod.xsltCompareStylesheetsEqual(self._o, other__o)
        return ret

    def newTransformContext(self, doc):
        """Create a new XSLT TransformContext"""
        if doc == None: doc__o = None
        else: doc__o = doc._o
        ret = libxsltmod.xsltNewTransformContext(self._o, doc__o)
        if ret == None: return None
        return transformCtxt(_obj=ret)

    def saveResultToString(self, result):
        """Have the stylesheet serialize the result of a
           transformation to a python string"""
        if result == None: result__o = None
        else: result__o = result._o
        ret = libxsltmod.xsltSaveResultToString(self._o, result__o)
        return ret

    def stylesheetHashCode(self):
        """Get the hash code of the stylesheet"""
        ret = libxsltmod.xsltGetStylesheetHashCode(self._o)
        return ret

    #
    # stylesheet functions from module variables
    #

    def parseGlobalParam(self, cur):
        """parse an XSLT transformation param declaration and record
           its value."""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        libxsltmod.xsltParseGlobalParam(self._o, cur__o)

    def parseGlobalVariable(self, cur):
        """Parses a global XSLT 'variable' declaration at compilation
           time and registers it"""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        libxsltmod.xsltParseGlobalVariable(self._o, cur__o)

    #
    # stylesheet functions from module xsltInternals
    #

    def allocateExtra(self):
        """Allocate an extra runtime information slot statically while
           compiling the stylesheet and return its number"""
        ret = libxsltmod.xsltAllocateExtra(self._o)
        return ret

    def compileAttr(self, attr):
        """Precompile an attribute in a stylesheet, basically it
          checks if it is an attrubute value template, and if yes
          establish some structures needed to process it at
           transformation time."""
        if attr == None: attr__o = None
        else: attr__o = attr._o
        libxsltmod.xsltCompileAttr(self._o, attr__o)

    def freeStylesheet(self):
        """Free up the memory allocated by @style"""
        libxsltmod.xsltFreeStylesheet(self._o)

    def parseStylesheetImportedDoc(self, doc):
        """parse an XSLT stylesheet building the associated structures
           except the processing not needed for imported documents."""
        if doc == None: doc__o = None
        else: doc__o = doc._o
        ret = libxsltmod.xsltParseStylesheetImportedDoc(doc__o, self._o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    def parseStylesheetOutput(self, cur):
        """parse an XSLT stylesheet output element and record
           information related to the stylesheet output"""
        if cur == None: cur__o = None
        else: cur__o = cur._o
        libxsltmod.xsltParseStylesheetOutput(self._o, cur__o)

    def parseStylesheetProcess(self, doc):
        """Parses an XSLT stylesheet, adding the associated
          structures. Called by: xsltParseStylesheetImportedDoc()
           (xslt.c) xsltParseStylesheetInclude() (imports.c)"""
        if doc == None: doc__o = None
        else: doc__o = doc._o
        ret = libxsltmod.xsltParseStylesheetProcess(self._o, doc__o)
        if ret == None: return None
        return stylesheet(_obj=ret)

    def parseTemplateContent(self, templ):
        """parse a template content-model Clean-up the template
          content from unwanted ignorable blank nodes and process
           xslt:text"""
        if templ == None: templ__o = None
        else: templ__o = templ._o
        libxsltmod.xsltParseTemplateContent(self._o, templ__o)

    #
    # stylesheet functions from module xsltutils
    #

    def cNsProp(self, node, name, nameSpace):
        """Similar to xmlGetNsProp() but with a slightly different
          semantic  Search and get the value of an attribute
          associated to a node This attribute has to be anchored in
          the namespace specified, or has no namespace and the
          element is in that namespace.  This does the entity
          substitution. This function looks in DTD attribute
          declaration for #FIXED or default declaration values unless
           DTD use has been turned off."""
        if node == None: node__o = None
        else: node__o = node._o
        ret = libxsltmod.xsltGetCNsProp(self._o, node__o, name, nameSpace)
        return ret

    def printErrorContext(self, ctxt, node):
        """Display the context of an error."""
        if ctxt == None: ctxt__o = None
        else: ctxt__o = ctxt._o
        if node == None: node__o = None
        else: node__o = node._o
        libxsltmod.xsltPrintErrorContext(ctxt__o, self._o, node__o)

    def saveResultToFd(self, fd, result):
        """Save the result @result obtained by applying the @style
          stylesheet to an open file descriptor This does not close
           the descriptor."""
        if result == None: result__o = None
        else: result__o = result._o
        ret = libxsltmod.xsltSaveResultToFd(fd, result__o, self._o)
        return ret

    def saveResultToFile(self, file, result):
        """Save the result @result obtained by applying the @style
          stylesheet to an open FILE * I/O. This does not close the
           FILE @file"""
        if result == None: result__o = None
        else: result__o = result._o
        ret = libxsltmod.xsltSaveResultToFile(file, result__o, self._o)
        return ret

    def saveResultToFilename(self, URL, result, compression):
        """Save the result @result obtained by applying the @style
           stylesheet to a file or @URL"""
        if result == None: result__o = None
        else: result__o = result._o
        ret = libxsltmod.xsltSaveResultToFilename(URL, result__o, self._o, compression)
        return ret

# xsltTransformState
XSLT_STATE_OK = 0
XSLT_STATE_ERROR = 1
XSLT_STATE_STOPPED = 2

# xsltDebugStatusCodes
XSLT_DEBUG_NONE = 0
XSLT_DEBUG_INIT = 1
XSLT_DEBUG_STEP = 2
XSLT_DEBUG_STEPOUT = 3
XSLT_DEBUG_NEXT = 4
XSLT_DEBUG_STOP = 5
XSLT_DEBUG_CONT = 6
XSLT_DEBUG_RUN = 7
XSLT_DEBUG_RUN_RESTART = 8
XSLT_DEBUG_QUIT = 9

# xsltOutputType
XSLT_OUTPUT_XML = 0
XSLT_OUTPUT_HTML = 1
XSLT_OUTPUT_TEXT = 2

# xsltErrorSeverityType
XSLT_ERROR_SEVERITY_ERROR = 0
XSLT_ERROR_SEVERITY_WARNING = 1

# xsltStyleType
XSLT_FUNC_COPY = 1
XSLT_FUNC_SORT = 2
XSLT_FUNC_TEXT = 3
XSLT_FUNC_ELEMENT = 4
XSLT_FUNC_ATTRIBUTE = 5
XSLT_FUNC_COMMENT = 6
XSLT_FUNC_PI = 7
XSLT_FUNC_COPYOF = 8
XSLT_FUNC_VALUEOF = 9
XSLT_FUNC_NUMBER = 10
XSLT_FUNC_APPLYIMPORTS = 11
XSLT_FUNC_CALLTEMPLATE = 12
XSLT_FUNC_APPLYTEMPLATES = 13
XSLT_FUNC_CHOOSE = 14
XSLT_FUNC_IF = 15
XSLT_FUNC_FOREACH = 16
XSLT_FUNC_DOCUMENT = 17
XSLT_FUNC_WITHPARAM = 18
XSLT_FUNC_PARAM = 19
XSLT_FUNC_VARIABLE = 20
XSLT_FUNC_WHEN = 21
XSLT_FUNC_EXTENSION = 22
XSLT_FUNC_OTHERWISE = 23
XSLT_FUNC_FALLBACK = 24
XSLT_FUNC_MESSAGE = 25
XSLT_FUNC_INCLUDE = 26
XSLT_FUNC_ATTRSET = 27
XSLT_FUNC_LITERAL_RESULT_ELEMENT = 28
XSLT_FUNC_UNKOWN_FORWARDS_COMPAT = 29

# xsltLoadType
XSLT_LOAD_START = 0
XSLT_LOAD_STYLESHEET = 1
XSLT_LOAD_DOCUMENT = 2

# xsltSecurityOption
XSLT_SECPREF_READ_FILE = 1
XSLT_SECPREF_WRITE_FILE = 2
XSLT_SECPREF_CREATE_DIRECTORY = 3
XSLT_SECPREF_READ_NETWORK = 4
XSLT_SECPREF_WRITE_NETWORK = 5

# xsltDebugTraceCodes
XSLT_TRACE_ALL = -1
XSLT_TRACE_NONE = 0
XSLT_TRACE_COPY_TEXT = 1
XSLT_TRACE_PROCESS_NODE = 2
XSLT_TRACE_APPLY_TEMPLATE = 4
XSLT_TRACE_COPY = 8
XSLT_TRACE_COMMENT = 16
XSLT_TRACE_PI = 32
XSLT_TRACE_COPY_OF = 64
XSLT_TRACE_VALUE_OF = 128
XSLT_TRACE_CALL_TEMPLATE = 256
XSLT_TRACE_APPLY_TEMPLATES = 512
XSLT_TRACE_CHOOSE = 1024
XSLT_TRACE_IF = 2048
XSLT_TRACE_FOR_EACH = 4096
XSLT_TRACE_STRIP_SPACES = 8192
XSLT_TRACE_TEMPLATES = 16384
XSLT_TRACE_KEYS = 32768
XSLT_TRACE_VARIABLES = 65536


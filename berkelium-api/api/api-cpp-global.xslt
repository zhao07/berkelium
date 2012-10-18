<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:variable name="lang">cpp</xsl:variable>
<xsl:variable name="class"></xsl:variable>

<xsl:output method="text"/>
<xsl:strip-space elements="*"/>

<xsl:include href="include.xslt"/>

<!-- ============================================================= -->
<!-- Header File                                                   -->
<!-- ============================================================= -->
<xsl:template match="/api">
	<!-- header -->
	<xsl:call-template name="comment-header"/>
	<xsl:call-template name="include-guard-start"/>
	<xsl:call-template name="comment-generated"/>

	<xsl:text>#include &lt;string&gt;
#include &lt;memory&gt;
#include &lt;cstdint&gt;

namespace Berkelium {

</xsl:text>

	<!-- forward defs -->
	<xsl:for-each select="/api/group">
		<!-- type -->
		<xsl:choose>
			<xsl:when test="@type='class'">
				<xsl:text>class </xsl:text>
			</xsl:when>
			<xsl:when test="@type='interface'">
				<xsl:text>class </xsl:text>
			</xsl:when>
			<xsl:otherwise>
				!!ERROR!!
			</xsl:otherwise>
		</xsl:choose>
		<xsl:value-of select="@name"/>
		<xsl:text>;
</xsl:text>
		<!-- type pointer -->
		<xsl:text>typedef std::shared_ptr&lt;</xsl:text>
		<xsl:value-of select="@name"/>
		<xsl:text>&gt; </xsl:text>
		<xsl:value-of select="@name"/>
		<xsl:text>Ref;

</xsl:text>

	</xsl:for-each>

	<xsl:text>} // namespace Berkelium

</xsl:text>
	<xsl:call-template name="include-guard-end"/>

</xsl:template>

</xsl:stylesheet>
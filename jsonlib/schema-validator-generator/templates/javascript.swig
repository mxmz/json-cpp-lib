
( function() {
        var definitions = {}

        {% for s in schemas %}
        {% set defs = s.defs %}

        // {{ JSON.stringify(s.desc) }} //
        /*
             {{ JSON.stringify(s.defs) }} 
        */   
        {% if defs.enum  %} // enum
         {% set values = defs.enum %}
         var enum_{{ loop.key }} = { {% for s in values %}{% if ! loop.first %},{%endif%} {{ JSON.stringify(s) }}: true{%endfor%} };
        {%endif%}
        function check_{{ loop.key }}( v ) { 
         var err;
         {% if defs.required %} // required
            {% set properties = defs.required %}
            {% for p in properties %}
                if ( v[{{ JSON.stringify(p) }}] === undefined   ) {
                    return "Missing attribute " + {{ JSON.stringify(p) }};
                }
            {%endfor%}
         {%endif%}

         {% if defs.type === 'string' %}
            if( ! typeof v === 'string' ) {
                    return "Expecting a string, but found: " + JSON.stringify(v);
            }

         {%endif%}

         {% if defs.properties %}  // properties {{ JSON.stringify(defs.properties) }}
            {% set properties = defs.properties %}
            {% for p in properties %}
             if ( v[{{ JSON.stringify(loop.key) }}] !== undefined   ) {
              if ( err = check_{{ p }} ( v[{{ JSON.stringify(loop.key) }}] ) ) {
                 return err;
              }
            }
            {%endfor%}
         {%endif%}

         {% if defs.oneOf %} // oneOf
            {% set subschemas = defs.oneOf %}
              err = 0;
             {% for ss in subschemas %}
              if ( null !== check_{{ ss }}(v) ) err++; // {{ schemas[ss].desc }}
              {%endfor%}
              if ( err !== {{ subschemas.length - 1 }} ) {
                        return "oneOf must match 1 and only one: " + {{ JSON.stringify( s.desc ) }} ;
              }
         {%endif%}
        
         {% if defs.allOf %} // oneOf
            {% set subschemas = defs.oneOf %}
              err = 0;
             {% for ss in subschemas %}
              if ( null !== check_{{ ss }}(v) ) err++; // {{ schemas[ss].desc }}
              {%endfor%}
              if ( err !== 0 ) {
                        return "allOf must match every schema: " + {{ JSON.stringify( s.desc ) }} ;
              }
         {%endif%}

         {% if defs.anyOf %} // oneOf
            {% set subschemas = defs.oneOf %}
              err = 0;
             {% for ss in subschemas %}
              if ( null !== check_{{ ss }}(v) ) err++; // {{ schemas[ss].desc }}
              {%endfor%}
              if ( err === {{ subschemas.length }} ) {
                        return "anyOf must match at least one: " + {{ JSON.stringify( s.desc ) }} ;
              }
         {%endif%}


         {% if defs.enum  %} // enum
            {% set values = defs.enum %}
            if ( enum_{{ loop.key }}[v] !== true   ) {
                            return "value must be one of: " + ({{ JSON.stringify(values) }}.join(", "));
             }
         {%endif%}
         return null;
        } 
        {%endfor%}



    {% for s in sources %}
    definitions.assert_{{ loop.key }} = function( v ) {
                if ( err = check_{{ s.schema }}(v) ) {
                    throw(err);
                }
    }
    definitions.check_{{ loop.key }} = check_{{ s.schema }};
    {%endfor%}


    // CommonJS
    if (typeof exports === "object") {
        module.exports = definitions;

    // RequireJS
    } else {
    
        {% for s in sources %}
        jschema_assert_{{ loop.key }} = definitions.assert_{{ loop.key }};
        jschema_check_{{ loop.key }} = definitions.check_{{ loop.key }};
        {%endfor%}
    }

})();


CREATE SEQUENCE sec_id_clientes
start with 10
increment by 10;

CREATE TABLE clientes (
    id_cliente INT DEFAULT nextval('sec_id_clientes'),
    nombre CHARACTER VARYING(30) NOT NULL,
    apellidos CHARACTER VARYING(30) NOT NULL,
    rfc CHARACTER VARYING(30) NOT NULL,
    direccion CHARACTER VARYING(30) NOT NULL,
    edad SMALLINT NOT NULL,
    pais CHARACTER VARYING(30) NOT NULL,

    CONSTRAINT pk_id_cliente PRIMARY KEY (id_cliente),
    CONSTRAINT ck_pais CHECK(pais ~ '^[Mexico]|[mexico]$'),
    CONSTRAINT ck_edad CHECK(edad >= 18)
);

CREATE TABLE cliente_telefonos(
    id_cliente_telefonos SMALLSERIAL,
    telefono CHARACTER VARYING(20) NOT NULL,
    id_cliente SMALLSERIAL NOT NULL,

    CONSTRAINT pk_cliente_telefonos PRIMARY KEY (id_cliente_telefonos),
    CONSTRAINT fk_cliente_telefonos_id_cliente_clientes FOREIGN KEY (id_cliente)
        REFERENCES clientes(id_cliente) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT ck_cliente_telefonos CHECK (telefono ~ '[\(]?[\+]?(\d{2}|\d{3})[\)]?[\s]?((\d{6}|\d{8})|(\d{3}[\*\.\-\s]){3}|(\d{2}[\*\.\-\s]){4}|(\d{4}[\*\.\-\s]){2})|\d{8}|\d{10}|\d{12}')
);

DROP TABLE clientes;

SELECT * FROM clientes;

INSERT INTO clientes VALUES (DEFAULT, 'Javier', 'Duran Flores', 'DUF010204', 'Ciudad Hidalgo', 21, 'Mexico');

INSERT INTO clientes VALUES (DEFAULT, 'Paula Gabriela', 'Gomez Merida', 'PGGM051705', 'Ciudad Hidalgo', 19, 'Mexico');

DROP TABLE clientes;
DROP SEQUENCE sec_id_clientes;

-- CREAR TABLA DE ARTICULOS
CREATE TABLE articulos (
    id_articulo SMALLSERIAL,
    descripcion CHARACTER VARYING(30) NOT NULL,
    cantidad INT DEFAULT 1,
    fecha_ingreso DATE NOT NULL,
    precio NUMERIC(12, 2) NOT NULL,
    descuento NUMERIC(12, 2),

    CONSTRAINT pk_id_articulo PRIMARY KEY (id_articulo),
    CONSTRAINT ck_fecha_ingreso CHECK (fecha_ingreso <= NOW())
);

-- ELIMINAR TABLA articulos
DROP TABLE articulos
INSERT INTO articulos VALUES (DEFAULT, 'Coca cola 3L', DEFAULT, '2022-10-03', 45.00, NULL);
INSERT INTO articulos VALUES (DEFAULT, 'Coca cola 3L', DEFAULT, '2022-10-05', 45.00, NULL);
INSERT INTO articulos VALUES (DEFAULT, 'Coca cola 3L', DEFAULT, '2022-10-04', 45.00, NULL);


-- MOSTRAR TABLA articulos
SELECT * FROM articulos;

-- TABLA DE FACTURAS
CREATE TABLE facturas(
    folio SMALLSERIAL,
    fecha_fact DATE DEFAULT NOW(),
    importe_total NUMERIC(12, 2) DEFAULT 0,
    importe_letra TEXT,
    id_cliente SMALLINT NOT NULL,

    CONSTRAINT pk_folio_factura PRIMARY KEY (folio),
    CONSTRAINT fk_facturas_id_cliente_clientes FOREIGN KEY (id_cliente)
        REFERENCES clientes (id_cliente) ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO clientes VALUES (DEFAULT, )

INSERT INTO facturas VALUES ('1', NOW(), 100.00, 'Cien', 20);
INSERT INTO facturas VALUES ('2', NOW(), 100.00, 'Cien', 30);

-- CREAR TABLA DETALLE_FACTURA
CREATE TABLE detalle_facturas(
    cns SMALLSERIAL,
    folio SMALLINT NOT NULL,
    id_articulo SMALLINT NOT NULL,
    cantidad INT NOT NULL,
    subtotal NUMERIC(12, 2) NOT NULL,

    CONSTRAINT pk_detalle_facturas_cns PRIMARY KEY (cns, folio),
    CONSTRAINT fk_detalle_facturas_folio_facturas FOREIGN KEY (folio)
        REFERENCES facturas (folio) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_detalle_facturas_id_articulo_articulos FOREIGN KEY(id_articulo)
        REFERENCES articulos (id_articulo) ON UPDATE CASCADE ON DELETE CASCADE
);

SELECT * FROM detalle_facturas;

SELECT subtotal FROM detalle_facturas INNER JOIN articulos ON detalle_facturas.id_articulo = articulos.id_articulo;

INSERT INTO detalle_facturas VALUES (1, '1', 3, 1, 1);
INSERT INTO detalle_facturas VALUES (2, '1', 3, 1, 0);
INSERT INTO detalle_facturas VALUES (3, '1', 3, 4, 0);
INSERT INTO detalle_facturas VALUES (4, '1', 3, 4, 0);
INSERT INTO detalle_facturas VALUES (5, '1', 3, 4, 0);
INSERT INTO detalle_facturas VALUES (6, '1', 3, 4, 0);
INSERT INTO detalle_facturas VALUES (7, '1', 3, 4, 0);



INSERT INTO detalle_facturas VALUES (9, '2', 3, 5, 1);
INSERT INTO detalle_facturas VALUES (10, '2', 3, 5, 1);
INSERT INTO detalle_facturas VALUES (11, '2', 3, 5, 1);
INSERT INTO detalle_facturas VALUES (12, '2', 3, 5, 1);
INSERT INTO detalle_facturas VALUES (13, '2', 3, 5, 1);
INSERT INTO detalle_facturas VALUES (14, '2', 3, 5, 1);

INSERT INTO detalle_facturas VALUES (15, '2', 3, 5, 1);


INSERT INTO detalle_facturas VALUES (21, '2', 3, 5, 1);

-- CREACION DE LA FUNCION cargar subtotal

CREATE OR REPLACE FUNCTION cargar_subtotal () RETURNS TRIGGER
AS
$$
    DECLARE 
        _subtotal NUMERIC;
    BEGIN
        SELECT (precio*detalle_facturas.cantidad) INTO _subtotal FROM detalle_facturas INNER JOIN articulos ON detalle_facturas.id_articulo = articulos.id_articulo WHERE new.cns = cns;
        UPDATE detalle_facturas SET subtotal = _subtotal WHERE cns = NEW.cns;

        RETURN NEW;
    END;
$$
LANGUAGE plpgsql;

-- CREACION DEL TRIGGER PARA crear automaticamente el subtotal

CREATE TRIGGER TR_INSERT_subtotal after INSERT ON detalle_facturas
for each row
execute procedure cargar_subtotal();


-- CREAR FUNCION PARA CALCULAR EL IMPORTE
CREATE OR REPLACE FUNCTION cargar_importe () RETURNS TRIGGER
AS
$$
    DECLARE 
        _importe_total NUMERIC := 0;
        _subtotal INT;
    BEGIN
        SELECT SUM(subtotal) INTO _importe_total FROM detalle_facturas WHERE folio = NEW.folio;

        SELECT (precio*detalle_facturas.cantidad) INTO _subtotal FROM detalle_facturas INNER JOIN articulos ON detalle_facturas.id_articulo = articulos.id_articulo WHERE new.cns = cns;

        UPDATE facturas SET importe_total = (_importe_total+_subtotal) WHERE folio = NEW.folio;

        RETURN NEW;
    END;
$$
LANGUAGE plpgsql;

-- CREACION DEL TRIGGER para crear el importe automaticamente
CREATE TRIGGER TR_INSERT_importe AFTER INSERT ON detalle_facturas
for each row
execute procedure cargar_importe();

CREATE TRIGGER TR_INSERT_importe_letra AFTER UPDATE OR INSERT ON facturas
for each row
execute procedure cargar_importe_letra();

INSERT INTO clientes VALUES ()
INSERT INTO facturas VALUES (DEFAULT, NOW(), NULL, NULL, 10);
INSERT INTO facturas VALUES (DEFAULT, NOW(), NULL, NULL, 10);
INSERT INTO detalle_facturas VALUES (DEFAULT, 4, 3, 2, 0)

-- FUNCION PARA CONVERTIR NUMERO A LETRAS

CREATE OR REPLACE FUNCTION cargar_importe_letra() RETURNS TRIGGER AS
$body$
DECLARE
     lnEntero INTEGER;
     lcRetorno TEXT;
     lnTerna INTEGER;
     lcMiles TEXT;
     lcCadena TEXT;
     lnUnidades INTEGER;
     lnDecenas INTEGER;
     lnCentenas INTEGER;
     lnFraccion INTEGER;
     lnSw INTEGER;
BEGIN
     lnEntero := FLOOR(new.importe_total)::INTEGER;--Obtenemos la parte Entera
     lnFraccion := FLOOR(((new.importe_total - lnEntero) * 100))::INTEGER;--Obtenemos la Fraccion del Monto
     lcRetorno := '';
     lnTerna := 1;
     IF lnEntero > 0 THEN
     lnSw := LENGTH(lnEntero::VARCHAR);
     WHILE lnTerna <= lnSw LOOP
        -- Recorro terna por terna
        lcCadena = '';
        lnUnidades = lnEntero % 10;
        lnEntero = CAST(lnEntero/10 AS INTEGER);
        lnDecenas = lnEntero % 10;
        lnEntero = CAST(lnEntero/10 AS INTEGER);
        lnCentenas = lnEntero % 10;
        lnEntero = CAST(lnEntero/10 AS INTEGER);
    -- Analizo las unidades
       SELECT
         CASE /* UNIDADES */
           WHEN lnUnidades = 1 AND lnTerna = 1 THEN 'UNO ' || lcCadena
           WHEN lnUnidades = 1 AND lnTerna <> 1 THEN 'UN ' || lcCadena
           WHEN lnUnidades = 2 THEN 'DOS ' || lcCadena
           WHEN lnUnidades = 3 THEN 'TRES ' || lcCadena
           WHEN lnUnidades = 4 THEN 'CUATRO ' || lcCadena
           WHEN lnUnidades = 5 THEN 'CINCO ' || lcCadena
           WHEN lnUnidades = 6 THEN 'SEIS ' || lcCadena
           WHEN lnUnidades = 7 THEN 'SIETE ' || lcCadena
           WHEN lnUnidades = 8 THEN 'OCHO ' || lcCadena
           WHEN lnUnidades = 9 THEN 'NUEVE ' || lcCadena
           ELSE lcCadena
          END INTO lcCadena;
          /* UNIDADES */
    -- Analizo las decenas
    SELECT
    CASE /* DECENAS */
      WHEN lnDecenas = 1 THEN
        CASE lnUnidades
          WHEN 0 THEN 'DIEZ '
          WHEN 1 THEN 'ONCE '
          WHEN 2 THEN 'DOCE '
          WHEN 3 THEN 'TRECE '
          WHEN 4 THEN 'CATORCE '
          WHEN 5 THEN 'QUINCE '
          ELSE 'DIECI' || lcCadena
        END
      WHEN lnDecenas = 2 AND lnUnidades = 0 THEN 'VEINTE ' || lcCadena
      WHEN lnDecenas = 2 AND lnUnidades <> 0 THEN 'VEINTI' || lcCadena
      WHEN lnDecenas = 3 AND lnUnidades = 0 THEN 'TREINTA ' || lcCadena
      WHEN lnDecenas = 3 AND lnUnidades <> 0 THEN 'TREINTA Y ' || lcCadena
      WHEN lnDecenas = 4 AND lnUnidades = 0 THEN 'CUARENTA ' || lcCadena
      WHEN lnDecenas = 4 AND lnUnidades <> 0 THEN 'CUARENTA Y ' || lcCadena
      WHEN lnDecenas = 5 AND lnUnidades = 0 THEN 'CINCUENTA ' || lcCadena
      WHEN lnDecenas = 5 AND lnUnidades <> 0 THEN 'CINCUENTA Y ' || lcCadena
      WHEN lnDecenas = 6 AND lnUnidades = 0 THEN 'SESENTA ' || lcCadena
      WHEN lnDecenas = 6 AND lnUnidades <> 0 THEN 'SESENTA Y ' || lcCadena
      WHEN lnDecenas = 7 AND lnUnidades = 0 THEN 'SETENTA ' || lcCadena
      WHEN lnDecenas = 7 AND lnUnidades <> 0 THEN 'SETENTA Y ' || lcCadena
      WHEN lnDecenas = 8 AND lnUnidades = 0 THEN 'OCHENTA ' || lcCadena
      WHEN lnDecenas = 8 AND lnUnidades <> 0 THEN 'OCHENTA Y ' || lcCadena
      WHEN lnDecenas = 9 AND lnUnidades = 0 THEN 'NOVENTA ' || lcCadena
      WHEN lnDecenas = 9 AND lnUnidades <> 0 THEN 'NOVENTA Y ' || lcCadena
      ELSE lcCadena
    END INTO lcCadena; /* DECENAS */
    -- Analizo las centenas
    SELECT
    CASE /* CENTENAS */
      WHEN lnCentenas = 1 AND lnUnidades = 0 AND lnDecenas = 0 THEN 'CIEN ' || lcCadena
      WHEN lnCentenas = 1 AND NOT(lnUnidades = 0 AND lnDecenas = 0) THEN 'CIENTO ' || lcCadena
      WHEN lnCentenas = 2 THEN 'DOSCIENTOS ' || lcCadena
      WHEN lnCentenas = 3 THEN 'TRESCIENTOS ' || lcCadena
      WHEN lnCentenas = 4 THEN 'CUATROCIENTOS ' || lcCadena
      WHEN lnCentenas = 5 THEN 'QUINIENTOS ' || lcCadena
      WHEN lnCentenas = 6 THEN 'SEISCIENTOS ' || lcCadena
      WHEN lnCentenas = 7 THEN 'SETECIENTOS ' || lcCadena
      WHEN lnCentenas = 8 THEN 'OCHOCIENTOS ' || lcCadena
      WHEN lnCentenas = 9 THEN 'NOVECIENTOS ' || lcCadena
      ELSE lcCadena
    END INTO lcCadena;/* CENTENAS */
    -- Analizo la terna
    SELECT
    CASE /* TERNA */
      WHEN lnTerna = 1 THEN lcCadena
      WHEN lnTerna = 2 AND (lnUnidades + lnDecenas + lnCentenas <> 0) THEN lcCadena || ' MIL '
      WHEN lnTerna = 3 AND (lnUnidades + lnDecenas + lnCentenas <> 0) AND
        lnUnidades = 1 AND lnDecenas = 0 AND lnCentenas = 0 THEN lcCadena || ' MILLON '
      WHEN lnTerna = 3 AND (lnUnidades + lnDecenas + lnCentenas <> 0) AND
        NOT (lnUnidades = 1 AND lnDecenas = 0 AND lnCentenas = 0) THEN lcCadena || ' MILLONES '
      WHEN lnTerna = 4 AND (lnUnidades + lnDecenas + lnCentenas <> 0) THEN lcCadena || ' MIL MILLONES '
      ELSE ''
    END INTO lcCadena;/* TERNA */

    --Retornamos los Valores Obtenidos
    lcRetorno = lcCadena  || lcRetorno;
    lnTerna = lnTerna + 1;
    END LOOP;
  END IF;
  IF lnTerna = 1 THEN
    lcRetorno := 'CERO';
  END IF;
  lcRetorno := RTRIM(lcRetorno::VARCHAR);

  UPDATE facturas SET importe_letra = lcRetorno::VARCHAR WHERE folio = new.folio;

RETURN NEW;
END;
$body$
LANGUAGE 'plpgsql' VOLATILE CALLED ON NULL INPUT SECURITY INVOKER;
 
COMMENT ON FUNCTION fu_numero_letras(numero numeric)
IS 'Funcion para Convertir el Monto Numerico a Letras';

CREATE TRIGGER TR_INSERT_importe_letra AFTER UPDATE ON facturas
for each row
execute procedure cargar_importe_letra();

CREATE OR REPLACE FUNCTION num2pal(numeric) RETURNS text LANGUAGE plperlu as $$
use Lingua::ES::Numeros;
$obj = new Lingua::ES::Numeros('FORMATO' => 'con %s.');
return $obj->real($_[0]);
$$;


-- FUNCION PARA nume	ro letra

CREATE OR REPLACE FUNCTION cargar_importe_letra() RETURNS TRIGGER
AS $$
	-- Función que devuelve la cadena de texto en castellano que corresponde a un número.
	-- Parámetros: número con 2 decimales, máximo 999.999.999,99.

	DECLARE	
		d varchar[];
		f varchar[];
		g varchar[];
		numt varchar;
		txt varchar;
		a integer;
		a1 integer;
		a2 integer;
		n integer;
		p integer;
		negativo boolean;
	BEGIN
		-- Máximo 999.999.999,99
		RAISE NOTICE 'Importe %', new.importe_total;
		if new.importe_total > 999999999.99 then
			return '---';
		end if;
		txt = '';
		d = array[' un',' dos',' tres',' cuatro',' cinco',' seis',' siete',' ocho',' nueve',' diez',' once',' doce',' trece',' catorce',' quince',
			' dieciseis',' diecisiete',' dieciocho',' diecinueve',' veinte',' veintiun',' veintidos', ' veintitres', ' veinticuatro', ' veinticinco',
			' veintiseis',' veintisiete',' veintiocho',' veintinueve'];
		f = array ['','',' treinta',' cuarenta',' cincuenta',' sesenta',' setenta',' ochenta', ' noventa'];
		g= array [' ciento',' doscientos',' trescientos',' cuatrocientos',' quinientos',' seiscientos',' setecientos',' ochocientos',' novecientos'];
		numt = lpad((numt::numeric(12,2))::text,12,'0');
		if strpos(numt,'-') > 0 then
		   negativo = true;
		else
		   negativo = false;
		end if;
		numt = translate(numt,'-','0');
		numt = translate(numt,'.,','');
		-- Trato 4 grupos: millones, miles, unidades y decimales
		p = 1;
		for i in 1..4 loop
			if i < 4 then
				n = substring(numt::text from p for 3);
			else
				n = substring(numt::text from p for 2);
			end if;
			p = p + 3;
			if i = 4 then
				if txt = '' then
					txt = ' cero';
				end if;
				if n > 0 then
				-- Empieza con los decimales
					txt = txt || ' con';
				end if;
			end if;
			-- Centenas 
			if n > 99 then
				a = substring(n::text from 1 for 1);
				a1 = substring(n::text from 2 for 2);
				if a = 1 then
					if a1 = 0 then
						txt = txt || ' cien';
					else
						txt = txt || ' ciento';
					end if;
				else
					txt = txt || g[a];
				end if;
			else
				a1 = n;
			end if;
			-- Decenas
			a = a1;
			if a > 0 then
				if a < 30 then
					if a = 21 and (i = 3 or i = 4) then
						txt = txt || ' veintiuno';
					elsif n = 1 and i = 2 then
						txt = txt; 
					elsif a = 1 and (i = 3 or i = 4)then
						txt = txt || ' uno';
					else
						txt = txt || d[a];
					end if;
				else
					a1 = substring(a::text from 1 for 1);
					a2 = substring(a::text from 2 for 1);
					if a2 = 1 and (i = 3 or i = 4) then
							txt = txt || f[a1] || ' y' || ' uno';
					else
						if a2 <> 0 then
							txt = txt || f[a1] || ' y' || d[a2];
						else
							txt = txt || f[a1];
						end if;
					end if;
				end if;
			end if;
			if n > 0 then
				if i = 1 then
					if n = 1 then
						txt = txt || ' millón';
					else
						txt = txt || ' millones';
					end if;
				elsif i = 2 then
					txt = txt || ' mil';
				end if;		
			end if;
		end loop;
		txt = ltrim(txt);
		if negativo = true then
		   txt= '-' || txt;
		end if;

		RAISE NOTICE 'Importe letra %', txt;
		UPDATE facturas SET importe_letra = txt WHERE folio = new.folio;
	   

	    RETURN new;
	END;
	$$
LANGUAGE plpgsql;

/* ELIMINAR TRIGGER Y FUNCION*/
DROP TRIGGER TR_INSERT_importe_letra on facturas;
DROP TABLA 

CREATE TRIGGER TR_INSERT_importe_letra AFTER UPDATE OR INSERT ON facturas
for each row
execute procedure cargar_importe_letra();

/* FUNCION PARA MOSTRAR TODOS LOS CLIENTES*/
CREATE OR REPLACE FUNCTION mostrar_clientes() RETURNS SETOF clientes 
AS
$BODY$

	BEGIN
		RETURN QUERY SELECT * FROM clientes;
	END;

$BODY$
LANGUAGE plpgsql;

-- FUNCION PARA MOSTRAR TODAS LAS FACTURAS
CREATE OR REPLACE FUNCTION mostrar_facturas() RETURNS SETOF facturas
AS
$BODY$
	BEGIN	
		RETURN QUERY SELECT * FROM facturas;
	END;
$BODY$
LANGUAGE plpgsql;

-- FUNCION PARA MOSTRAR TODOS LOS DETALLES FACTURAS
CREATE OR REPLACE FUNCTION mostrar_detalle_facturas() RETURNS SETOF detalle_facturas
AS
$BODY$
	BEGIN
		RETURN QUERY SELECT * FROM detalle_facturas;
	END;
	$BODY$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION mostrar_articulos() RETURNS SETOF articulos
AS
$BODY$
	BEGIN
		RETURN QUERY SELECT * FROM articulos;
	END;
	$BODY$
LANGUAGE plpgsql;

--  FUNCIONES DE INSERCIONES

--  FUNCION PARA INSERTAR UN CLIENTE
CREATE OR REPLACE FUNCTION insertar_cliente(CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING,
					    CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING) 
RETURNS VOID
AS
$BODY$
	BEGIN
		INSERT INTO clientes (nombre, apellidos, rfc, direccion, edad, pais) VALUES ($1, $2, $3, $4, $5::SMALLINT, $6);
		RAISE NOTICE 'Se agrego el cliente correctamente';
	END;
	$BODY$
LANGUAGE plpgsql;

-- FUNCION PARA INSERTAR TELEFONOS CLIENTES
CREATE OR REPLACE FUNCTION insertar_cliente_telefonos (CHARACTER VARYING, CHARACTER VARYING)
RETURNS VOID
AS
$BODY$
	BEGIN
		INSERT INTO cliente_telefonos (telefono, id_cliente) VALUES ($1, $2::SMALLINT);
	END;
$BODY$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION insertar_articulos(CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING,
					      CHARACTER VARYING, CHARACTER VARYING)
RETURNS VOID
AS
$BODY$
	BEGIN
		INSERT INTO articulos (descripcion, cantidad, fecha_ingreso, precio, descuento) VALUES ($1, $2::INT, $3::DATE, $4::NUMERIC, $5::NUMERIC);
	END;
$BODY$
LANGUAGE plpgsql;

--  FUNCION PARA INSERTAR NUEVAS FACTURAS
CREATE OR REPLACE FUNCTION insertar_factura (CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING,CHARACTER VARYING)
RETURNS VOID
AS
$BODY$
	BEGIN
		INSERT INTO facturas (fecha_fact, importe_total, importe_letra, id_cliente) VALUES ($1::DATE, $2::NUMERIC, $3::TEXT, $4::SMALLINT);
		RAISE NOTICE 'Se agrego la factura correctamente';
	END;
$BODY$
LANGUAGE plpgsql;

-- CREAR FUNCION PARA INGRESAR FACTURAS - SOLO ID
CREATE OR REPLACE FUNCTION insertar_facturas_id_cliente(CHARACTER VARYING) 
RETURNS VOID
AS
$BODY$
	BEGIN 
		INSERT INTO Facturas (id_cliente) VALUES ($1::SMALLINT);
	END;
$BODY$
LANGUAGE plpgsql;

-- FUNCION PARA INSERTAR NUEVOS DETALLES DE LA FACTURA
CREATE OR REPLACE FUNCTION insertar_detalle_factura (CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING,CHARACTER VARYING)
RETURNS VOID
AS
$BODY$
	BEGIN
		INSERT INTO detalle_facturas (folio, id_articulo, cantidad, subtotal) VALUES ($1::SMALLINT, $2::SMALLINT, $3::INT, $4::NUMERIC);
	END;
$BODY$
LANGUAGE plpgsql;

--FUNCION PARA ACTUALIZAR LOS CLIENTES
CREATE OR REPLACE FUNCTION actualizar (_columna CHARACTER VARYING, _nuevo CHARACTER VARYING, 
        _id CHARACTER VARYING, _tabla CHARACTER VARYING)
RETURNS VOID AS
$BODY$  
	BEGIN
		IF _tabla = 'clientes' THEN
			IF _columna = 'nombre' THEN
				UPDATE clientes SET nombre = _nuevo WHERE id_cliente = _id::INT;
			ELSIF _columna = 'apellidos' THEN
				UPDATE clientes SET apellidos = _nuevo WHERE id_cliente = _id::INT;
			ELSIF _columna = 'rfc' THEN
				UPDATE clientes SET rfc = _nuevo WHERE id_cliente = _id::INT;
			ELSIF _columna = 'direccion' THEN
				UPDATE clientes SET direccion = _nuevo WHERE id_cliente = _id::INT;
			ELSIF _columna = 'edad' THEN
				UPDATE clientes SET edad = _nuevo::INT WHERE id_cliente = _id::INT;
			ELSIF _columna = 'pais' THEN
				UPDATE clientes SET pais = _nuevo WHERE id_cliente = _id::INT;
			END IF;
		ELSIF _tabla= 'facturas' THEN
			IF _columna = 'fecha_fact' THEN
				UPDATE facturas SET fecha_fact = _nuevo::DATE WHERE folio = _id::INT;
			ELSIF _columna = 'importe_total' THEN
				UPDATE facturas SET importe_total = _nuevo::NUMERIC WHERE folio = _id::INT;
			ELSIF _columna = 'importe_letra' THEN
				UPDATE facturas SET importe_letra = _nuevo WHERE folio = _id::INT;
			ELSIF _columna = 'id_cliente' THEN
				UPDATE facturas SET id_cliente = _nuevo::SMALLINT WHERE folio = _id::INT;
			END IF;
		ELSIF _tabla= 'detalle_facturas' THEN
			IF _columna = 'folio' THEN
				UPDATE detalle_facturas SET folio = _nuevo::SMALLINT WHERE cns = _id::INT;
			ELSIF _columna = 'id_articulo' THEN
				UPDATE detalle_facturas SET id_articulo = _nuevo::SMALLINT WHERE cns = _id::INT;
			ELSIF _columna = 'cantidad' THEN
				UPDATE detalle_facturas SET cantidad = _nuevo::INT WHERE cns = _id::INT;
			ELSIF _columna = 'subtotal' THEN
				UPDATE detalle_facturas SET subtotal = _nuevo::NUMERIC WHERE cns = _id::INT;
			END IF;
		ELSIF _tabla= 'cliente_telefonos' THEN
			IF _columna = 'telefono' THEN
				UPDATE cliente_telefonos SET telefono = _nuevo WHERE id_cliente_telefonos = _id::INT;
			ELSIF _columna = 'id_cliente' THEN
				UPDATE cliente_telefonos SET id_cliente = _nuevo::SMALLINT WHERE id_cliente_telefonos = _id::INT;
			END IF;
		ELSIF _tabla= 'articulos' THEN
			IF _columna = 'descripcion' THEN
				UPDATE articulos SET descripcion = _nuevo WHERE id_articulo = _id::INT;
			ELSIF _columna = 'cantidad' THEN
				UPDATE articulos SET cantidad = _nuevo::INT WHERE id_articulo = _id::INT;
			ELSIF _columna = 'fecha_ingreso' THEN
				UPDATE articulos SET fecha_ingreso = _nuevo::DATE WHERE id_articulo = _id::INT;
			ELSIF _columna = 'precio' THEN
				UPDATE articulos SET precio = _nuevo::NUMERIC WHERE id_articulo = _id::INT;
			ELSIF _columna = 'descuento' THEN
				UPDATE articulos SET descuento = _nuevo::NUMERIC WHERE id_articulo = _id::INT;
			END IF;
		END IF;
	END;
$BODY$
LANGUAGE plpgsql;


-- FUNCIONES PARA ELIMINAR
-- FUNCION PARA ELIMINAR ARTICULO POR SU ID
CREATE OR REPLACE FUNCTION eliminar_articulo(INT)
RETURNS VOID AS
$BODY$
    BEGIN
        DELETE FROM articulos WHERE id_articulo = $1::SMALLINT;
    END;
$BODY$
LANGUAGE plpgsql;
-- FUNCION PARA ELIMINAR CLIENTE POR SU ID
CREATE OR REPLACE FUNCTION eliminar_cliente(INT)
RETURNS VOID AS
$BODY$
    BEGIN
        DELETE FROM clientes WHERE id_cliente = $1::SMALLINT;
END;
$BODY$
LANGUAGE plpgsql;
-- FUNCION PARA ELIMINAR FACTURA POR SU ID
CREATE OR REPLACE FUNCTION eliminar_factura(INT)
RETURNS VOID AS
$BODY$
    BEGIN
        DELETE FROM facturas WHERE id_factura = $1::SMALLINT;
    END;
$BODY$
LANGUAGE plpgsql;
-- FUNCION PARA ELIMINAR FACTURA POR SU ID
CREATE OR REPLACE FUNCTION eliminar_detalle_factura(INT)
RETURNS VOID AS
$BODY$
  
    BEGIN
        DELETE FROM detalle_facturas WHERE cns = $1::SMALLINT;
    END;  
$BODY$
LANGUAGE plpgsql;

-- CREAR VIEW de Facturas con su detalle 
CREATE VIEW vista_facturas
AS 

SELECT * FROM facturas
natural JOIN detalle_facturas
NATURAL JOIN articulos;


-- MOSTRAR FACTURAS CON CLIENTE
SELECT folio, id_cliente, nombre, fecha_fact, importe_total, importe_letra FROM 
facturas
NATURAL JOIN
clientes;

-- CREAR VIEW FACTURAS TODAS
CREATE VIEW vista_facturas_todas
AS
SELECT * FROM facturas;

-- FUNCION para buscar facturas por id
CREATE OR REPLACE FUNCTION mostrar_facturas_x_folio(CHARACTER VARYING)	
RETURNS VOID AS		
$BODY$
    BEGIN
        SELECT * FROM facturas WHERE folio = $1;



SELECT facturas.folio, fecha_fact, importe_total | importe_letra | id_cliente
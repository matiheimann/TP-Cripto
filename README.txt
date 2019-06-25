
# Criptografia y Seguridad Informática 
## Trabajo Práctico de Implementación: 
## Secreto compartido en imágenes con estanografía 

               
### Manual de uso 

> ./ss [-d|-r] -s <imagen> -m <imagen> -k <número> -n <número> -l <directorio>

## Descripcion
-d:
    Indica que se va a distribuir una imagen en otras imágenes
     
-r:
    indica que se va a recuperar una imagen secreta a partir de otras imágenes

-s imagen:
    El nombre imagen corresponde al path de un archivo de extensión .bmp. En el
    caso de que se haya elegido la opción (-d) este archivo debe existir ya que es la imagen a
    ocultar y debe ser una imagen en blanco y negro (8 bits por pixel). Si se eligió la opción (-r)
    éste archivo será el archivo de salida, con la imagen secreta revelada al finalizar el programa.
      
-m imagen:
    El nombre imagen corresponde al path de un archivo con extensión .bmp. En el
    caso de que se haya elegido la opción (-d) este archivo es una imagen en blanco y negro que
    servirá como “marca de agua” para verificar todo el proceso. Debe ser de igual tamaño que la
    imagen secreta. En el caso de que se haya elegido la opción (-r) este archivo es una imagen en
    blanco y negro que contiene la transformación de la imagen de “marca de agua”.
    
-k número:
    El número corresponde a la cantidad mínima de sombras necesarias para recuperar el secreto en
    un esquema (k, n)

-n número:
    El número corresponde a la cantidad total de sombras en las que se distribuirá el secreto en un
    esquema (k, n).

-l directorio:
    El directorio donde se encuentran las imágenes en las que se distribuirá el
    secreto (en el caso de que se haya elegido la opción (-d)), o donde están las imágenes que
    contienen oculto el secreto ( en el caso de que se haya elegido la opción (-r)). Debe contener
    imágenes de extensión .bmp, de 24 bits por pixel. En caso de que este directorio contenga algo que no sean imagenes bmp de 24 bits por pixel, el programa abortara la ejecucion informandose este error.

### Notas

* Al recuperar la imagen secreta, se generara una imagen llamada "Watermark.bmp" en el directorio donde se encuentra el programa. Esta imagen es la llamada "marca de agua", que se obtiene a partir de Rw.

* Al distribuir la imagen secreta, se generara una imagen llamada "RW.bmp" en el directorio donde se encuentra el programa. Esta imagen es una imagen en blanco y negro, con ruido, que contiene la transformacion de la marca de agua.

### Ejemplo
* Distribuir la imagen “Albert.bmp” con watermark “Paris.bmp” según esquema (4,8)
guardando las sombras en imágenes del directorio “color280x440”:

> ./ss –d –s /home/User/Desktop/Images/Albert.bmp –m home/User/Desktop/Images/Paris.bmp –k 4 – n 8 –l color280x440/


* Recuperar la imagen “secreto.bmp”, con watermark “RW.bmp” en un esquema (4,8) buscando imágenes en el directorio color280x440/

> ./ss –r –s /home/User/Desktop/Secrets/secreto.bmp –m /RW/RW.bmp –k 4 –n 8 –l color280x440/

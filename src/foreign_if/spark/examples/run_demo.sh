#!/bin/sh

LIBRARY_PATH=../lib/
JARS=../lib/frovedis_client.jar
COMMAND="mpirun -np 2 ../../server/frovedis_server"
#COMMAND="mpirun -np 1 $FROVEDIS_SERVER" 
#LIBRARY_PATH=$X86_INSTALLPATH/lib
#JARS=$X86_INSTALLPATH/lib/spark/frovedis_client.jar

# by default, Spark runs as local mode
# if you use distributed mode, put the input files to HDFS
# hadoop fs -put ./input

if [ ! -d out ]; then
	mkdir out
fi

echo " --- executing data transfer demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_data_transfer.jar "$COMMAND"

echo " --- executing frovedis matrix demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_mat.jar "$COMMAND"

echo " --- executing frovedis dataframe demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_df.jar "$COMMAND"

echo " --- executing frovedis wrapper demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_pblas_scalapack.jar "$COMMAND"

echo " --- executing frovedis sparse svd demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_svd.jar "$COMMAND"

echo " --- executing frovedis pca demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_pca.jar "$COMMAND"

echo " --- executing frovedis logistic regression with sgd demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_lrsgd.jar "$COMMAND"

echo " --- executing frovedis logistic regression model operations demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_lrm.jar  "$COMMAND"

echo " --- executing frovedis naive bayes demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_nb.jar "$COMMAND"

echo " --- executing frovedis decision tree demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_dt.jar "$COMMAND"

echo " --- executing frovedis factorization machine demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_fm.jar "$COMMAND"

echo " --- executing frovedis recommendation demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_als.jar "$COMMAND"

echo " --- executing frovedis kmeans demo ---"
spark-submit --driver-java-options "-Djava.library.path=$LIBRARY_PATH" --jars $JARS --conf spark.driver.memory=8g lib/spark2frovedis_kmeans.jar "$COMMAND"

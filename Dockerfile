FROM nvidia/cuda:10.0-devel-ubuntu18.04

RUN apt-get update && apt-get install -y python3 python3-pip libtbb-dev zlib1g-dev libboost-python-dev wget git alien dpkg-dev debhelper build-essential ffmpeg

RUN rm /usr/bin/python && ln -s /usr/bin/python3 /usr/bin/python

RUN pip3 install pybind11 numpy torch torchvision pytest scikit-image

# Install Intel Embree
RUN wget https://github.com/embree/embree/releases/download/v3.2.4/embree-3.2.4.x86_64.rpm.tar.gz && tar xzf embree-3.2.4.x86_64.rpm.tar.gz
RUN alien embree3-lib-3.2.4-1.x86_64.rpm && alien embree3-devel-3.2.4-1.noarch.rpm && alien embree3-examples-3.2.4-1.x86_64.rpm && \
    dpkg -i embree3-lib_3.2.4-2_amd64.deb && dpkg -i embree3-devel_3.2.4-2_all.deb && dpkg -i embree3-examples_3.2.4-2_amd64.deb

# Clone Redner
RUN git clone --recursive https://github.com/onai/inverse-rendering.git

# LDL
ENV LD_LIBRARY_PATH /usr/local/lib/:/usr/local/lib64/:/usr/local/cuda/lib64:/usr/lib64/:/redner/NVIDIA-OptiX-SDK-5.1.1-linux64/lib64/:$LD_LIBRARY_PATH
ENV PATH /usr/local/cuda/bin:$PATH

# Install OpenEXR
RUN wget https://github.com/openexr/openexr/releases/download/v2.3.0/ilmbase-2.3.0.tar.gz
RUN tar xvfz ilmbase-2.3.0.tar.gz && cd ilmbase-2.3.0 && ./configure && make -j install

RUN wget https://github.com/openexr/openexr/releases/download/v2.3.0/openexr-2.3.0.tar.gz
RUN tar xvzf openexr-2.3.0.tar.gz && cd openexr-2.3.0 && ./configure  --disable-ilmbasetest && make -j install

# Install OpenEXR python
RUN pip3 install openexr

# Install cmake 12
RUN wget https://cmake.org/files/v3.13/cmake-3.13.0-Linux-x86_64.sh
RUN chmod +x cmake-3.13.0-Linux-x86_64.sh && ./cmake-3.13.0-Linux-x86_64.sh --skip-license --exclude-subdir --prefix=/usr/local

# Install OptiX
RUN wget https://s3-us-west-1.amazonaws.com/oce-build-downloads/NVIDIA-OptiX-SDK-5.1.1-linux64-25109142.sh
RUN chmod +x NVIDIA-OptiX-SDK-5.1.1-linux64-25109142.sh
RUN ./NVIDIA-OptiX-SDK-5.1.1-linux64-25109142.sh --skip-license --prefix=/redner --include-subdir

# Install pybind11
RUN git clone https://github.com/pybind/pybind11.git
RUN cd pybind11 && mkdir build && cd build && cmake .. && make install -j

# Install redner
RUN cd inverse-rendering && mkdir build && cd build && cmake .. -DOptiX_INSTALL_DIR=/redner/NVIDIA-OptiX-SDK-5.1.1-linux64/ -DOptiX_INCLUDE=/redner/NVIDIA-OptiX-SDK-5.1.1-linux64/include -DEMBREE_INCLUDE_PATH=/usr/include/embree3 -DEMBREE_LIBRARY=/usr/lib64/libembree3.so.3 && make install -j

# RUN test
RUN cd inverse-rendering && cd tests && python3 test_two_triangles.py

ENTRYPOINT ["/bin/bash"]

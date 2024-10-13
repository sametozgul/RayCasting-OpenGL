#include "OGLRenderer.h"
#include "PositionGenerator.h"
int g_selected_sphere = -1;
OGLRenderer::OGLRenderer(GLFWwindow* win)
{
    mRenderData.rdWindow = win;
}

bool OGLRenderer::init(unsigned int width, unsigned int height)
{
    mRenderData.rdWidth = width;
    mRenderData.rdHeight = height;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::log(1,"%s :Failed to initialize GLAD.\n",__FUNCTION__);
        return false;
    }
    if (!GLAD_GL_VERSION_4_6) {
        Logger::log(1, "%s error: failed to get at least OpenGL 4.6\n", __FUNCTION__);
        return false;
    }
    mShader.loadShaders("Debug/shaders/Fragment.vert","Debug/shaders/Fragment.frag");
    mShader.use();
    mUniformBuffer.init();
    Logger::log(1,"%s : OpenGL Renderer is initialized.\n",__FUNCTION__);
    mUserInterface.init(mRenderData);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&mRenderData.rdNrAttributes);
    mTriangle = std::make_unique<Rectangle>();
    mTriangle->init();
    rectanglePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    mVertexBuffer.init();
    return true;
}

void OGLRenderer::resize(unsigned int width, unsigned int height)
{
    mRenderData.rdWidth = width;
    mRenderData.rdHeight = height;
    glViewport(0,0,width,height);
}
void ::OGLRenderer::draw()
{
    double tickTime = glfwGetTime();
    mRenderData.rdTickDiff = tickTime - mLastTickTime;

    mRenderData.rdFrameTime = mFrameTimer.stop();
    mFrameTimer.start();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mRenderData.rdUsePolygonMode)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(mRenderData.rdIsColorChanged)
    {
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) +0.5f;
        glUniform4f(mRenderData.rdVertexColorPosition, 0.0f, greenValue, 0.0f, 1.0f);
    }
    else{
        glUniform4f(mRenderData.rdVertexColorPosition,0.5,0.5,0.5,1.0);
    }
    // mTexture.bind();
    mVertexBuffer.uploadData(mTriangle->getData());
    mShader.use();
    mModelMatrix = glm::mat4(1.0f);
    mViewMatrix = glm::mat4(1.0f);
     mViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                              glm::vec3(0.0f, 0.0f, 0.0f),
                              glm::vec3(0.0f, 1.0f, 0.0f));
    mProjectionMatrix = glm::perspective(glm::radians(45.0f),(float)mRenderData.rdWidth/(float)mRenderData.rdHeight,0.1f,100.0f);
    mShader.setMat4(mModelMatrix,"model");
    mUniformBuffer.uploadUniformObjData(mViewMatrix,mProjectionMatrix);
    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        if ( g_selected_sphere == i ) {
            mShader.setFloat(1.0f,"blue");
        } else {
            mShader.setFloat(0.0f,"blue");
        }
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, rectanglePositions[i]);
        mShader.setMat4(model,"model");

        mVertexBuffer.bindAndDraw(GL_TRIANGLES, 0, 6);
    }


    glBindVertexArray(0);
    mUserInterface.createFrame(mRenderData);
    mUserInterface.render();

    mLastTickTime = tickTime;

}


void OGLRenderer::handleMousePressEvents(double xPos, double yPos)
{
    mRenderData.rdXLastPos = xPos;
    mRenderData.rdYLastPos = yPos;
    glm::vec3 ray_wor = getRay( (float)xPos, (float)yPos );

    int closest_plane_clicked = -1;
    float closest_intersection = 0.0f;
    for(auto i = 0; i < rectanglePositions.size(); ++i){
        if (intersectDisc(glm::vec3(0.0f,0.0f,3.0f), ray_wor, glm::vec3(0.0f,0.0f,1.0f), rectanglePositions[i], 0.5f)) {
            if( -1 == closest_plane_clicked ){
                closest_plane_clicked = i;
                g_selected_sphere = closest_plane_clicked;
            }
        }
    }
    std::cout << closest_plane_clicked << std::endl;

    mFirstMouse = true;
}

void OGLRenderer::handleMouseReleasedEvents()
{
    mFirstMouse = false;
}

void OGLRenderer::cleanUp()
{
    mUserInterface.cleanUp();
    mShader.cleanup();
    mVertexBuffer.cleanup();
}

glm::vec3 OGLRenderer::getRay(float xPos, float yPos) {
    float x = ( 2.0f * xPos ) / mRenderData.rdWidth - 1.0f;
    float y = 1.0f - ( 2.0f * yPos ) / mRenderData.rdHeight;
    float z = 1.0f;
    glm::vec3 ray_nds = glm::vec3( x, y, z );
    glm::vec4 ray_clip = glm::vec4( ray_nds.x, ray_nds.y, -1.0, 1.0 );
    glm::vec4 ray_eye = inverse( mProjectionMatrix ) * ray_clip;
    ray_eye = glm::vec4( ray_eye.x, ray_eye.y, -1.0, 0.0 );
    glm::vec3 ray_wor = glm::vec3( inverse( mViewMatrix ) * ray_eye );
    return ray_wor;
}
glm::vec3 OGLRenderer::normalise( const glm::vec3& v ) {
    glm::vec3 vb;
    float l = length( v );
    if ( 0.0f == l ) { return glm::vec3( 0.0f, 0.0f, 0.0f ); }
    vb.x = v.x / l;
    vb.y = v.y / l;
    vb.z = v.z / l;
    return vb;
}
bool OGLRenderer::intersectRayPlane(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                       const glm::vec3& planeNormal, const glm::vec3& planePoint,
                       float& t) {
    float denominator = glm::dot(planeNormal, rayDirection);
    if (fabs(denominator) < 1e-6) {
        return false; // No intersection
    }
    t = glm::dot(planeNormal, planePoint - rayOrigin) / denominator;
    return t >= 0;
}
bool OGLRenderer::intersectDisc(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                                const glm::vec3& planeNormal, const glm::vec3& planePoint,
                                const float& radius){
    float t = 0.0f;
    if(intersectRayPlane(rayOrigin, rayDirection, planeNormal, planePoint, t)){
        glm::vec3 p = rayOrigin + rayDirection * t;
        glm::vec3 v = p - planePoint;
        float d2 = glm::dot(v,v);
        return d2 <= radius * radius;
    }
    return false;
}

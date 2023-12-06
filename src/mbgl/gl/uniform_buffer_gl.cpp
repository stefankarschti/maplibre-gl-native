#include <mbgl/gl/uniform_buffer_gl.hpp>
#include <mbgl/gl/defines.hpp>
#include <mbgl/platform/gl_functions.hpp>
#include <mbgl/util/compression.hpp>
#include <mbgl/util/logging.hpp>

#include <cassert>
#include <cstring>

namespace mbgl {
namespace gl {

using namespace platform;

UniformBufferGL::UniformBufferGL(const void* data_, std::size_t size_)
    : UniformBuffer(size_),
      hash(util::crc32(data_, size_)),
      current(new uint8_t[size])
    {
    MBGL_CHECK_ERROR(glGenBuffers(1, &id));
    MBGL_CHECK_ERROR(glBindBuffer(GL_UNIFORM_BUFFER, id));
    MBGL_CHECK_ERROR(glBufferData(GL_UNIFORM_BUFFER, size, data_, GL_DYNAMIC_DRAW));
    MBGL_CHECK_ERROR(glBindBuffer(GL_UNIFORM_BUFFER, 0));
        
    std::memset(current.get(), 0, size);
}

UniformBufferGL::UniformBufferGL(const UniformBufferGL& other)
    : UniformBuffer(other),
      hash(other.hash),
      current(new uint8_t[other.size])
{
    MBGL_CHECK_ERROR(glGenBuffers(1, &id));
    MBGL_CHECK_ERROR(glCopyBufferSubData(other.id, id, 0, 0, size));
    MBGL_CHECK_ERROR(glBindBuffer(GL_COPY_READ_BUFFER, other.id));
    MBGL_CHECK_ERROR(glBindBuffer(GL_COPY_WRITE_BUFFER, id));
    MBGL_CHECK_ERROR(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size));

    std::memcpy(current.get(), other.current.get(), size);
}

UniformBufferGL::~UniformBufferGL() {
    if (id) {
        MBGL_CHECK_ERROR(glDeleteBuffers(1, &id));
        id = 0;
    }
}

void UniformBufferGL::update(const void* data_, std::size_t size_) {
    assert(size == size_);
    if (size != size_) {
        Log::Error(
            Event::General,
            "Mismatched size given to UBO update, expected " + std::to_string(size) + ", got " + std::to_string(size_));
        return;
    }

    const uint32_t newHash = util::crc32(data_, size_);
    if (newHash != hash) {
        hash = newHash;
        MBGL_CHECK_ERROR(glBindBuffer(GL_UNIFORM_BUFFER, id));
        MBGL_CHECK_ERROR(glBufferSubData(GL_UNIFORM_BUFFER, 0, size_, data_));
        MBGL_CHECK_ERROR(glBindBuffer(GL_UNIFORM_BUFFER, 0));
        std::memcpy(current.get(), data_, size);
    }
}

} // namespace gl
} // namespace mbgl
